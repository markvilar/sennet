#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <zedutils/active_messaging/container_device.hpp>
#include <zedutils/active_messaging/runtime.hpp>

namespace zed { namespace am {

runtime::runtime(
	std::string port,
	std::function<void(runtime&)> f,
	boost::uint64_t wait_for
	)
	: m_io_service(),
	m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::tcp::v4(), 
		boost::lexical_cast<boost::uint16_t>(port))),	
	m_connections(),
	m_exec_thread(),
	m_parcel_queue(64), // Pre-allocate some nodes
	m_local_queue(64), // Pre-allocate some nodes
	m_stop_flag(false),
	m_main(f),
	m_wait_for(wait_for)
{
	// Make sure we are waiting for some clients.
	BOOST_ASSERT(wait_for != 0);
}

void runtime::start()
{
	// Set up acceptor. 
	// 	- Option 'reuse_address' allows the socket to be bound to an
	// 		address that is already in use.
	// 	- Option 'linger' specifies if socket should linger on close if
	// 		unsent data is present.
	m_acceptor.set_option(
		boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.set_option(
		boost::asio::ip::tcp::acceptor::linger(true, 0));
	
	// Start execution thread.
	m_exec_thread = 
		std::thread(boost::bind(&runtime::exec_loop, boost::ref(*this)));
	
	// Start accepting connections.
	async_accept();
}

void runtime::stop()
{
	// Tell the execution thread to stop.
	m_stop_flag.store(true);

	// Destroy the keep-alive work object, which will cause run() to return
	// when all I/O work is done.
	m_io_service.stop();
}

void runtime::run()
{
	// Keep io_service::run() from returning.
	boost::asio::io_service::work work(m_io_service);

	m_io_service.run();

	if (m_exec_thread.joinable())
		m_exec_thread.join();
}

std::shared_ptr<connection> runtime::connect(
	std::string host,
	std::string port
	)
{
	// Set up resolver and query.
	boost::asio::ip::tcp::resolver resolver(m_io_service);
	boost::asio::ip::tcp::resolver::query query(
		boost::asio::ip::tcp::v4(), host, port);
	
	// Initialize iterators.
	boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
	boost::asio::ip::tcp::resolver::iterator end;

	// Iterate over list of entries from resolving the query.
	for (boost::asio::ip::tcp::resolver::iterator i = it; i != end; ++i)
		// If the runtime already has a connection established with the 
		// endpoint.
		if (m_connections.count(*i) != 0)
			return m_connections[*i];

	// If there are no existing connections to host, initialize new 
	// connection.
	std::shared_ptr<connection> conn(new connection(*this));

	// Wait for some time for the Runtime to become available.
	// TODO: Look into adding a more general connection timer!
	for (boost::uint64_t i = 0; i < 64; ++i)
	{
		boost::system::error_code ec;
		boost::asio::connect(conn->get_socket(), it, ec);
		if (!ec) break;

		// Otherwise, sleep and try again.
		std::chrono::milliseconds period(100);
		std::this_thread::sleep_for(period);
	}

	// Set connection socket options. 
	// 	- Option 'reuse_address' allows the socket to be bound to an
	// 		address that is already in use.
	// 	- Option 'linger' specifies if socket should linger on close if
	// 		unsent data is present.

	conn->get_socket().set_option(
		boost::asio::ip::tcp::socket::reuse_address(true));
	conn->get_socket().set_option(
		boost::asio::ip::tcp::socket::linger(true, 0));

	// Note that if there were multiple I/O threads, one would have to lock
	// before accessing the connection map.
	boost::asio::ip::tcp::endpoint ep = conn->get_remote_endpoint();
	BOOST_ASSERT(m_connections.count(ep) == 0);

	m_connections[ep] = conn;

	// Start the connection by calling the async. read operation.
	conn->async_read();

	return conn;
}

void runtime::async_accept()
{
	std::shared_ptr<connection> conn;
	conn.reset(new connection(*this));

	// Set up async. accept operation with handle_accept() as completion
	// handler.
	m_acceptor.async_accept(conn->get_socket(),
		boost::bind(&runtime::handle_accept,
			boost::ref(*this),
			boost::asio::placeholders::error,
			conn));
}

void runtime::handle_accept(
	boost::system::error_code const& error,
	std::shared_ptr<connection> conn
	)
{
	if (!error)
	{
		// If there was no error, then we need to insert conn into the
		// connection table, but first the next async_accept() is set
		// up.
		std::shared_ptr<connection> old_conn(conn);

		// Initialize new connection.
		conn.reset(new connection(*this));

		// Set up new async. accept operation with handle_accept() as
		// completion handler.
		m_acceptor.async_accept(conn->get_socket(),
			boost::bind(&runtime::handle_accept,
				boost::ref(*this),
				boost::asio::placeholders::error,
				conn));
		
		// Note that if there were multiple I/O threads, we would have
		// to lock before touching the map.
		boost::asio::ip::tcp::endpoint ep =
			old_conn->get_remote_endpoint();
		BOOST_ASSERT(m_connections.count(ep) == 0);

		// Add accepted connection to connections.	
		m_connections[ep] = old_conn;

		// If main exists, do we have enough clients to run it?
		if (m_main && (m_connections.size() >= m_wait_for))
		{
			// Instead of running main directly, we will stick it in
			// the action queue.
			m_local_queue.push(
				new std::function<void(runtime&)>(m_main));
		}

		// Start read from the accepted connection.
		old_conn->async_read();
	}
}

void runtime::exec_loop()
{
	while (!m_stop_flag.load())
	{
		// Look for pending actions to execute.
		std::function<void(runtime&)>* act_ptr = 0;

		if (m_local_queue.pop(act_ptr))
		{
			// Check action validity.
			BOOST_ASSERT(act_ptr);

			// Extract action.
			boost::scoped_ptr<std::function<void(runtime&)>>
				act(act_ptr);

			// Execute action.
			(*act)(*this);
		}

		// If there's no pending actions, find parcel to deserialize and
		// execute.
		std::vector<char>* raw_msg_ptr = 0;

		if (m_parcel_queue.pop(raw_msg_ptr))
		{
			// Extract raw message.
			boost::scoped_ptr<std::vector<char>> 
				raw_msg(raw_msg_ptr);

			// Create action from raw message.
			boost::scoped_ptr<action>
				act(deserialize_parcel(*raw_msg));

			// Execute action.
			(*act)(*this);
		}
	}
}

std::vector<char>* runtime::serialize_parcel(action const& act)
{
	// TODO: Look more into this!
	std::vector<char>* raw_msg_ptr = new std::vector<char>();

	// Define I/O type.
	typedef container_device<std::vector<char>> io_device_type;

	// Create I/O stream in order to serialize action into parcel with an
	// archive.
	boost::iostreams::stream<io_device_type> io(*raw_msg_ptr);

	// Initialize action pointer to be input to archive.
	action const* act_ptr = &act;

	// Local scope in order to make sure archive goes out of scope before
	// proceeding.
	{
		boost::archive::binary_oarchive archive(io);
		archive & act_ptr;
	}

	return raw_msg_ptr;
}

action* runtime::deserialize_parcel(std::vector<char>& raw_msg)
{
	// Define I/O type.
	typedef container_device<std::vector<char>> io_device_type;

	// Create I/O stream in order to deserialize parcel into action with an
	// archive.
	boost::iostreams::stream<io_device_type> io(raw_msg);

	action* act_ptr = 0;

	// Local scope in order to make sure archive goes out of scope before
	// proceeding.
	{
		boost::archive::binary_iarchive archive(io);
		archive & act_ptr;
	}

	BOOST_ASSERT(act_ptr);

	return act_ptr;
}

} // namespace am
}; // namespace zed

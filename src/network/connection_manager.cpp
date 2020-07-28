#include <sennet/network/connection_manager.hpp>

#include <sennet/core/base.hpp>

#include <sennet/network/container_device.hpp>

#include <boost/bind.hpp>

namespace sennet 
{

connection_manager::connection_manager(std::string port, 
	boost::uint64_t wait_for)
	: m_io_service(),
	m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::tcp::v4(), 
		boost::lexical_cast<boost::uint16_t>(port))),
	m_connections(),
	m_exec_thread(),
	m_inbound_queue(64),
	m_outbound_queue(64),
	m_stop_flag(false),
	m_wait_for(wait_for)
{
	// Make sure we are waiting for some clients.
	BOOST_ASSERT(wait_for != 0);
}

connection_manager::~connection_manager()
{ 
	stop(); 
}

boost::asio::io_service& connection_manager::get_io_service() 
{ 
	return m_io_service; 
}

boost::lockfree::queue<std::vector<char>*>& connection_manager::get_inbound_queue()
{ 
	return m_inbound_queue;
}

boost::lockfree::queue<message*>& connection_manager::get_outbound_queue()
{
	return m_outbound_queue;
}

std::map<boost::asio::ip::tcp::endpoint, ref<connection>>& 
	connection_manager::get_connections()
{
	return m_connections;
}

ref<connection> connection_manager::find_connection(const std::string& addr,
	const unsigned short port)
{
	auto conns = get_connections();
	auto it = conns.begin();
	while (it != conns.end())
	{
		if (it->first.address().to_string() == addr and 
			it->first.port() == port)
			return it->second;
		++it;
	}
	return nullptr;
}

void connection_manager::start()
{
	// Set up acceptor. 
	// 	- Option 'reuse_address' allows the socket to be bound to an
	// 		address that is already in use.
	// 	- Option 'linger' specifies if socket should linger on close if
	// 		unsent data is present.
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::linger(true, 0));

	// Start execution thread.
	m_exec_thread = std::thread(std::bind(&connection_manager::exec_loop,
		this));
	
	// Start accepting connections.
	async_accept();
}

void connection_manager::stop()
{
	// Tell the execution thread to stop.
	m_stop_flag = true;

	// Destroy the keep-alive work object, which will cause run() to return
	// when all I/O work is done.
	m_io_service.stop();
}

void connection_manager::run()
{
	// Keep io_service::run() from returning.
	boost::asio::io_service::work work(m_io_service);

	m_io_service.run();

	if (m_exec_thread.joinable())
		m_exec_thread.join();
}

ref<connection> connection_manager::connect(std::string host, 
	std::string port)
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
		// If the connection_manager already has a connection 
		// established with the endpoint.
		if (m_connections.count(*i) != 0)
			return m_connections[*i];

	// If there are no existing connections to host, initialize new 
	// connection.
	auto conn = create_ref<connection>(get_io_service());

	// Wait for some time for the connection manager to become available.
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
	conn->get_socket().set_option(boost::asio::ip::tcp::socket::reuse_address(
		true));
	conn->get_socket().set_option(boost::asio::ip::tcp::socket::linger(
		true, 0));
		
	// Note that if there were multiple I/O threads, one would have to lock
	// before accessing the connection map.
	boost::asio::ip::tcp::endpoint ep = conn->get_remote_endpoint();
	BOOST_ASSERT(m_connections.count(ep) == 0);

	m_connections[ep] = conn;

	// Start the connection by calling the async. read operation.
	conn->async_read();

	return conn;
}

void connection_manager::async_accept()
{
	ref<connection> conn = create_ref<connection>(get_io_service());

	// Set up async. accept operation with handle_accept() as completion
	// handler.
	m_acceptor.async_accept(conn->get_socket(),
		boost::bind(&connection_manager::handle_accept,
			boost::ref(*this),
			boost::asio::placeholders::error,
			conn));
}

void connection_manager::handle_accept(boost::system::error_code const& error,
	std::shared_ptr<connection> conn)
{
	if (!error)
	{
		// If there was no error, then we need to insert conn into the
		// connection table, but first the next async_accept() is set
		// up.
		std::shared_ptr<connection> old_conn(conn);

		// Initialize new connection.
		conn.reset(new connection(get_io_service()));

		// Set up new async. accept operation with handle_accept() as
		// completion handler.
		m_acceptor.async_accept(conn->get_socket(),
			boost::bind(&connection_manager::handle_accept,
				boost::ref(*this), boost::asio::placeholders::error,
				conn));
		
		// Note that if there were multiple I/O threads, we would have
		// to lock before touching the map.
		boost::asio::ip::tcp::endpoint ep =
			old_conn->get_remote_endpoint();
		BOOST_ASSERT(m_connections.count(ep) == 0);

		// Add accepted connection to connections.	
		m_connections[ep] = old_conn;

		// Start read from the accepted connection.
		old_conn->async_read();
	}
}

void connection_manager::exec_loop()
{
	while (!m_stop_flag)
	{
		// Look for pending actions that has been posted locally to 
		// execute.
		message* msg_ptr = nullptr;

		if (m_outbound_queue.pop(msg_ptr))
		{
			// Check action validity.
			BOOST_ASSERT(msg_ptr);
			
			// TODO: Add async_write_worker callback.
		}

		// If there's no pending actions, find parcel to deserialize and
		// execute.
		std::vector<char>* raw_msg_ptr = nullptr;

		if (m_inbound_queue.pop(raw_msg_ptr))
		{
			// Extract raw message.
			boost::scoped_ptr<std::vector<char>> 
				raw_msg(raw_msg_ptr);

			// Create action from raw message.
			boost::scoped_ptr<message>
				msg(deserialize_parcel(*raw_msg));
			
			// TODO: Add message callback.
		}
	}
}

std::vector<char>* connection_manager::serialize_parcel(const message& msg)
{
	std::vector<char>* raw_msg_ptr = new std::vector<char>();

	// Define I/O type.
	typedef container_device<std::vector<char>> io_device_type;

	// Create I/O stream in order to serialize action into parcel with an
	// archive.
	boost::iostreams::stream<io_device_type> io(*raw_msg_ptr);

	// Initialize action pointer to be input to archive.
	message const* msg_ptr = &msg;

	// Local scope in order to make sure archive goes out of scope before
	// proceeding.
	{
		boost::archive::binary_oarchive archive(io);
		archive & msg_ptr;
	}

	return raw_msg_ptr;
}

message* connection_manager::deserialize_parcel(std::vector<char>& raw_msg)
{
	// Define I/O type.
	typedef container_device<std::vector<char>> io_device_type;

	// Create I/O stream in order to deserialize parcel into action with an
	// archive.
	boost::iostreams::stream<io_device_type> io(raw_msg);

	message* msg_ptr = nullptr;

	// Local scope in order to make sure archive goes out of scope before
	// proceeding.
	{
		boost::archive::binary_iarchive archive(io);
		archive & msg_ptr;
	}

	BOOST_ASSERT(msg_ptr);

	return msg_ptr;
}

}

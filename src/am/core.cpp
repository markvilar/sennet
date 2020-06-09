#include <zedutils/am/container_device.hpp>
#include <zedutils/am/core.hpp>

namespace am {

// --------------------------------- connection --------------------------------

connection::connection(runtime& rt)
	: m_runtime(rt), 
	m_socket(rt.get_io_service()),
	m_in_size(0),
	m_in_buffer()
{
}

connection::~connection()
{
	// Ensure a graceful shutdown.
	if (m_socket.is_open())
	{
		boost::system::error_code ec;
		m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
			ec);
		m_socket.close(ec);
	}
}

boost::asio::ip::tcp::endpoint connection::get_remote_endpoint() const
{
	return m_socket.remote_endpoint();
}

boost::asio::ip::tcp::endpoint connection::get_local_endpoint() const
{
	return m_socket.local_endpoint();
}

void connection::async_read()
{
	// Check that the in buffer is NULL.
	BOOST_ASSERT(m_in_buffer == 0);

	// Set up attributes for a new read.
	m_in_size = 0;
	m_in_buffer = new std::vector<char>();

	// Set up the async. read operation and bind the member function
	// handle_read_size() as completion handler.
	boost::asio::async_read(m_socket,
		boost::asio::buffer(&m_in_size, sizeof(m_in_size)),
		boost::bind(&connection::handle_read_size,
			shared_from_this(),
			boost::asio::placeholders::error));
}

void connection::async_write(action::base_action const& act)
{
	// Create a default function if a handler is not specified.
	std::function<void(boost::system::error_code const&)> h;

	// Start async. write operation with the default function.
	async_write(act, h);
}

void connection::async_write(
	action::base_action const& act,
	std::function<void(boost::system::error_code const&)> handler
	)
{
	// Create a shared pointer to a clone of the action to make sure it
	// stays alive.
	std::shared_ptr<action::base_action> act_ptr(act.clone());

	// Add the action async_write_worker(act_ptr, handler) to the runtime
	// action queue.
	m_runtime.get_local_queue().push(new std::function<void(runtime&)>(
		boost::bind(&connection::async_write_worker,
			shared_from_this(), act_ptr, handler)));
}

void connection::async_write_worker(
	std::shared_ptr<action::base_action> act,
	std::function<void(boost::system::error_code const&)> handler
	)
{
	// Serialize the action parcel and add it to an out buffer.
	std::shared_ptr<std::vector<char>> 
		out_buffer(m_runtime.serialize_parcel(*act));
	
	// Get out buffer size.
	std::shared_ptr<boost::uint64_t>
		out_size(new boost::uint64_t(out_buffer->size()));

	// Set up buffers for the out size and out buffer.
	std::vector<boost::asio::const_buffer> buffers;
	buffers.push_back(boost::asio::buffer(&*out_size, sizeof(*out_size)));
	buffers.push_back(boost::asio::buffer(*out_buffer));

	// Set up async. write operation with handler_write() as completion
	// handler.
	boost::asio::async_write(m_socket, buffers,
		boost::bind(&connection::handle_write,
			shared_from_this(),
			boost::asio::placeholders::error,
			out_size,
			out_buffer,
			handler));
}

void connection::handle_read_size(boost::system::error_code const& error)
{
	// Return if an error has occured.
	if (error) return;

	// Check that the in buffer is valid.
	BOOST_ASSERT(m_in_buffer);

	// Resize the in buffer to the in size.
	(*m_in_buffer).resize(m_in_size);

	// Set up async. read operation for the in data with handle_read_data()
	// as completion handler.
	boost::asio::async_read(m_socket,
		boost::asio::buffer(*m_in_buffer),
		boost::bind(&connection::handle_read_data,
			shared_from_this(),
			boost::asio::placeholders::error));
}

void connection::handle_read_data(boost::system::error_code const& error)
{
	// Return if an error has occured.
	if (error) return;

	// Extract raw message.
	std::vector<char>* raw_msg = 0;
	std::swap(m_in_buffer, raw_msg);

	// Add raw message to runtime queue.
	m_runtime.get_parcel_queue().push(raw_msg);

	// Start next async. read operation.
	async_read();
}

void connection::handle_write(
	boost::system::error_code const& error,
	std::shared_ptr<boost::uint64_t> out_size,
	std::shared_ptr<std::vector<char>> out_buffer,
	std::function<void(boost::system::error_code const&)> handler
	)
{
	if (handler)
		handler(error);
}


// ---------------------------------- runtime ----------------------------------

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

std::shared_ptr<connection> runtime::find_connection(
	const std::string& addr
	)
{
	// Get the runtime connections.
	auto conns = get_connections();
	auto it = conns.begin();
	while (it != conns.end())
	{
		if (it->first.address().to_string() == addr)
			return it->second;
		++it;
	}
	return nullptr;
}

std::shared_ptr<connection> runtime::find_connection(
	const std::string& addr,
	const unsigned short port
	)
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
	std::cout << "Executing runtime's execution loop!\n";
	while (!m_stop_flag.load())
	{
		// Look for pending actions that has been posted locally to 
		// execute.
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
			boost::scoped_ptr<action::base_action>
				act(deserialize_parcel(*raw_msg));
			
			// Execute action.
			(*act)(*this);
		}
	}
}

std::vector<char>* runtime::serialize_parcel(action::base_action const& act)
{
	// TODO: Look more into this!
	std::vector<char>* raw_msg_ptr = new std::vector<char>();

	// Define I/O type.
	typedef container_device<std::vector<char>> io_device_type;

	// Create I/O stream in order to serialize action into parcel with an
	// archive.
	boost::iostreams::stream<io_device_type> io(*raw_msg_ptr);

	// Initialize action pointer to be input to archive.
	action::base_action const* act_ptr = &act;

	// Local scope in order to make sure archive goes out of scope before
	// proceeding.
	{
		boost::archive::binary_oarchive archive(io);
		archive & act_ptr;
	}

	return raw_msg_ptr;
}

action::base_action* runtime::deserialize_parcel(std::vector<char>& raw_msg)
{
	// Define I/O type.
	typedef container_device<std::vector<char>> io_device_type;

	// Create I/O stream in order to deserialize parcel into action with an
	// archive.
	boost::iostreams::stream<io_device_type> io(raw_msg);

	action::base_action* act_ptr = 0;

	// Local scope in order to make sure archive goes out of scope before
	// proceeding.
	{
		boost::archive::binary_iarchive archive(io);
		archive & act_ptr;
	}

	BOOST_ASSERT(act_ptr);

	return act_ptr;
}


// -------------------------------- zed_runtime --------------------------------

zed_runtime::zed_runtime(
	std::string port,
	std::string root,
	std::function<void(runtime&)> f,
	boost::uint64_t wait_for
	)
	: runtime(port, f, wait_for),
	m_zed(),
	m_root(root)
{
}

zed_runtime::~zed_runtime()
{
	// Stop I/O service and execution thread.
	stop();

	// Close camera.
	close_zed();
}

sl::ERROR_CODE zed_runtime::open_zed(sl::InitParameters& init_params)
{
	// TODO: Assertions?
	return m_zed.open(init_params);
}

void zed_runtime::close_zed()
{
	// TODO: Assertions?
	if (is_zed_opened())
		m_zed.close();
}

bool zed_runtime::is_zed_opened()
{
	// TODO: Assertions?
	return m_zed.isOpened();
}

bool zed_runtime::is_zed_recording()
{
	// TODO: Assertions?
	return zed_recording_status().is_recording;
}

sl::RecordingStatus zed_runtime::zed_recording_status()
{
	// TODO: Assertions?
	return m_zed.getRecordingStatus();
}

sl::RecordingParameters zed_runtime::zed_recording_parameters()
{
	// TODO: Assertions?
	return m_zed.getRecordingParameters();
}

sl::ERROR_CODE zed_runtime::enable_zed_recording(
	sl::RecordingParameters rec_params
	)
{
	// TODO: Assertions?
	return m_zed.enableRecording(rec_params);
}

void zed_runtime::disable_zed_recording()
{
	// TODO: Assertions?
	m_zed.disableRecording();
}

sl::ERROR_CODE zed_runtime::retrieve_zed_image(
	sl::Mat& m,
	sl::VIEW view,
	sl::MEM mem,
	sl::Resolution res
	)
{
	return m_zed.retrieveImage(m, view, mem, res);
}

sl::Timestamp zed_runtime::get_zed_timestamp(sl::TIME_REFERENCE& ref)
{
	return m_zed.getTimestamp(ref);
}

void zed_runtime::exec_loop()
{
	std::cout << "Executing zed_runtime's execution loop!\n";
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
			boost::scoped_ptr<action::base_action>
				act(deserialize_parcel(*raw_msg));
			
			// Execute action.
			(*act)(*this);
		}
	}
}

}; // namespace am

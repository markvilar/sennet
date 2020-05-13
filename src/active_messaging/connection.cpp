#include <zedutils/active_messaging/connection.hpp>

namespace zed { namespace am {

connection::connection(runtime& rt)
	: m_runtime(rt), 
	m_socket(rt.get_io_service()),
	m_in_size(0),
	m_in_buffer()
{
}

boost::asio::ip::tcp::endpoint connection::get_remote_endpoint() const
{
	return m_socket.remote_endpoint();
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

void connection::async_write(action const& act)
{
	// Create a default function if a handler is not specified.
	std::function<void(boost::system::error_code const&)> h;

	// Start async. write operation with the default function.
	async_write(act, h);
}

void connection::async_write(
	action const& act,
	std::function<void(boost::system::error_code const&)> handler
	)
{
	// Create a shared pointer to a clone of the action to make sure it
	// stays alive.
	std::shared_ptr<action> act_ptr(act.clone());

	// Add the action async_write_worker(act_ptr, handler) to the runtime
	// action queue.
	m_runtime.get_local_queue().push(new std::function<void(runtime&)>(
		boost::bind(&connection::async_write_worker,
			shared_from_this(), act_ptr, handler)));
}

void connection::async_write_worker(
	std::shared_ptr<action> act,
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

} // namespace am
}; // namespace zed

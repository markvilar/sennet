#include <sennet/network/connection.hpp>

#include <sennet/messages/message.hpp>

#include <boost/bind.hpp>

namespace sennet
{

connection::connection(boost::asio::io_service& service)
	: m_socket(service),
	m_in_size(0),
	m_in_buffer(nullptr)
{
}

connection::~connection()
{
	if (m_socket.is_open())
	{
		boost::system::error_code ec;
		m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
			ec);
		m_socket.close(ec);
	}
}

boost::asio::ip::tcp::socket& connection::get_socket()
{ 
	return m_socket; 
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

	boost::asio::async_read(m_socket,
		boost::asio::buffer(&m_in_size, sizeof(m_in_size)),
		boost::bind(&connection::handle_read_size, shared_from_this(),
			boost::asio::placeholders::error));
}

void connection::async_write(const message& msg)
{
	// Create a default function if a handler is not specified.
	std::function<void(boost::system::error_code const&)> h;

	// Start async. write operation with the default function.
	async_write(msg, h);
}

void connection::async_write(const message& msg,
	std::function<void(boost::system::error_code const&)> handler)
{
	std::shared_ptr<message> msg_ptr(msg.clone());

	// TODO: Fix!
	// m_manager.get_local_queue().push(msg_ptr);
}

void connection::async_write_worker(const message& msg,
	std::function<void(boost::system::error_code const&)> handler)
{
	// TODO: Fix
	// Serialize the action parcel and add it to an out buffer.
	// std::shared_ptr<std::vector<char>> 
		//out_buffer(m_manager.serialize_parcel(*msg));

	// Temporary
	std::shared_ptr<std::vector<char>> out_buffer(new std::vector<char>());
	
	// Get out buffer size.
	std::shared_ptr<boost::uint64_t>
		out_size(new boost::uint64_t(out_buffer->size()));

	// Set up buffers for the out size and out buffer.
	std::vector<boost::asio::const_buffer> buffers;
	buffers.push_back(boost::asio::buffer(&*out_size, sizeof(*out_size)));
	buffers.push_back(boost::asio::buffer(*out_buffer));

	// Set up async. write operation with handle_write() as completion
	// handler.
	boost::asio::async_write(m_socket, buffers,
		boost::bind(&connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error, out_size,
			out_buffer, handler));
			
}

void connection::handle_read_size(boost::system::error_code const& error)
{
	// Return if an error has occured.
	if (error) return;

	// Check that the in buffer is valid.
	BOOST_ASSERT(m_in_buffer);

	// Resize the in buffer to the in size.
	(*m_in_buffer).resize(m_in_size);

	// TODO: Look into adding a macro for the handler binding!
	// Set up async. read operation for the in data with handle_read_data()
	// as completion handler.
	boost::asio::async_read(m_socket, boost::asio::buffer(*m_in_buffer),
		boost::bind(&connection::handle_read_data, shared_from_this(),
		boost::asio::placeholders::error));
}

void connection::handle_read_data(boost::system::error_code const& error)
{
	// Return if an error has occured.
	if (error) return;

	// Extract raw message.
	std::vector<char>* raw_msg = nullptr;
	std::swap(m_in_buffer, raw_msg);

	// TODO: Add on_parcel callback!
	// Add raw message to parcel queue.
	// m_manager.get_parcel_queue().push(raw_msg);

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

}

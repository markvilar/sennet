#include <sennet/network/connection.hpp>

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

void connection::set_parcel_callback(const parcel_callback_fn& callback)
{
	m_parcel_callback = callback;
}

void connection::async_read()
{
	// Check that the in buffer is NULL.
	SN_CORE_ASSERT(m_in_buffer == 0, "In buffer is null!");

	// Set up attributes for a new read.
	m_in_size = 0;
	m_in_buffer = new parcel();

	boost::asio::async_read(m_socket,
		boost::asio::buffer(&m_in_size, sizeof(m_in_size)),
		std::bind(&connection::on_read_size, shared_from_this(),
		std::placeholders::_1));
}

void connection::async_write(std::shared_ptr<parcel> out_buffer)
{
	// Get out buffer size.
	std::shared_ptr<uint64_t> out_size(new uint64_t(out_buffer->size()));

	// Set up buffers for the out size and out buffer.
	std::vector<boost::asio::const_buffer> buffers;
	buffers.push_back(boost::asio::buffer(&*out_size, sizeof(*out_size)));
	buffers.push_back(boost::asio::buffer(*out_buffer));

	// Set up async. write operation with on_write() as completion
	// handler.
	boost::asio::async_write(m_socket, buffers,
		std::bind(&connection::on_write, shared_from_this(),
		std::placeholders::_1, out_size, out_buffer));
}

void connection::on_read_size(const boost::system::error_code& error)
{
	// Return if an error has occured.
	if (error) return;

	// Check that the in buffer is valid.
	SN_CORE_ASSERT(m_in_buffer, "In on_read_size: In buffer is null!");

	// Resize the in buffer to the in size.
	(*m_in_buffer).resize(m_in_size);

	// TODO: Look into adding a macro for the handler binding!
	// Set up async. read operation for the in data with on_read_data()
	// as completion handler.
	boost::asio::async_read(m_socket, boost::asio::buffer(*m_in_buffer),
		std::bind(&connection::on_read_data, shared_from_this(),
		std::placeholders::_1));
}

void connection::on_read_data(const boost::system::error_code& error)
{
	// Return if an error has occured.
	if (error)
	{
		SN_CORE_ERROR("Error in on_read_data: {0}", error.message());
		return;
	}

	// Extract raw message.
	parcel* raw_msg = nullptr;
	std::swap(m_in_buffer, raw_msg);

	if (m_parcel_callback)
	{
		SN_CORE_ASSERT(raw_msg, 
			"In on_read_data: Raw message point is null");
		m_parcel_callback(raw_msg);
	}
	else if (raw_msg)
	{
		SN_CORE_WARN("In on_read_data: No parcel callback function.");
	}

	// Start next async. read operation.
	async_read();
}

void connection::on_write(const boost::system::error_code& error,
	std::shared_ptr<uint64_t> out_size, std::shared_ptr<parcel> out_buffer)
	
{
	if (error)
	{
		SN_CORE_ERROR("Error in on_write: {0}", error.message());
	}
}

}

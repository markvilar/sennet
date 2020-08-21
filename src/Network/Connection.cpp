#include <Sennet/pch.hpp>
#include <Sennet/Network/Connection.hpp>

namespace Sennet
{

Connection::Connection(asio::io_service& service)
	: m_Socket(service),
	m_InSize(0),
	m_InBuffer(nullptr)
{
}

Connection::~Connection()
{
	if (m_Socket.is_open())
	{
		asio::error_code ec;
		m_Socket.shutdown(asio::ip::tcp::socket::shutdown_both,
			ec);
		m_Socket.close(ec);
	}
}

asio::ip::tcp::socket& Connection::GetSocket()
{ 
	return m_Socket; 
}

asio::ip::tcp::endpoint Connection::GetRemoteEndpoint() const
{
	return m_Socket.remote_endpoint();
}

asio::ip::tcp::endpoint Connection::GetLocalEndpoint() const
{
	return m_Socket.local_endpoint();
}

std::pair<std::string, unsigned short> Connection::GetRemoteInformation() const
{
	return {m_Socket.remote_endpoint().address().to_string(),
		m_Socket.remote_endpoint().port() };
}

std::pair<std::string, unsigned short> Connection::GetLocalInformation() const
{
	return {m_Socket.local_endpoint().address().to_string(),
		m_Socket.local_endpoint().port() };
}

void Connection::SetDataCallback(const DataCallbackFn& callback)
{
	m_DataCallback = callback;
}

void Connection::AsyncRead()
{
	// Check that the in buffer is NULL.
	SN_CORE_ASSERT(m_InBuffer == nullptr, "In buffer is not null!");

	// Set up attributes for a new read.
	m_InSize = 0;
	m_InBuffer = CreateRef<MessageEncoding>();

	asio::async_read(m_Socket,
		asio::buffer(&m_InSize, sizeof(m_InSize)),
		std::bind(&Connection::OnReadSize, shared_from_this(),
		std::placeholders::_1));
}

void Connection::AsyncWrite(Ref<MessageEncoding> outBuffer)
{
	// Get out buffer size.
	std::shared_ptr<uint64_t> outSize(new uint64_t(outBuffer->size()));

	// Set up buffers for the out size and out buffer.
	std::vector<asio::const_buffer> buffers;
	buffers.push_back(asio::buffer(&*outSize, sizeof(*outSize)));
	buffers.push_back(asio::buffer(*outBuffer));

	// Set up async. write operation with on_write() as completion
	// handler.
	asio::async_write(m_Socket, buffers,
		std::bind(&Connection::OnWrite, shared_from_this(),
		std::placeholders::_1, outSize, outBuffer));
}

void Connection::OnReadSize(const asio::error_code& error)
{
	// Return if an error has occured.
	if (error) return;

	// Check that the in buffer is valid.
	SN_CORE_ASSERT(m_InBuffer, "In on_read_size: In buffer is null!");

	// Resize the in buffer to the in size.
	(*m_InBuffer).resize(m_InSize);

	// Set up async. read operation for the in data with on_read_data()
	// as completion handler.
	asio::async_read(m_Socket, asio::buffer(*m_InBuffer),
		std::bind(&Connection::OnReadData, shared_from_this(),
		std::placeholders::_1));
}

void Connection::OnReadData(const asio::error_code& error)
{
	// Return if an error has occured.
	if (error)
	{
		SN_CORE_ERROR("Error in on_read_data: {0}", error.message());
		return;
	}

	// Extract raw message.
	Ref<MessageEncoding> rawMsg = nullptr;
	std::swap(m_InBuffer, rawMsg);

	if (m_DataCallback)
	{
		SN_CORE_ASSERT(rawMsg, 
			"In on_read_data: Raw message point is null");
		m_DataCallback(rawMsg);
	}
	else if (!m_DataCallback)
	{
		SN_CORE_WARN("In on_read_data: No data callback.");
	}

	// Start next async. read operation.
	AsyncRead();
}

void Connection::OnWrite(const asio::error_code& error,
	Ref<uint64_t> outSize, Ref<MessageEncoding> outBuffer)
{
	if (error)
	{
		SN_CORE_ERROR("Error in on_write: {0}", error.message());
	}
}

}

#include "Sennet/pch.hpp"
#include "Sennet/Network/Connection.hpp"

namespace Sennet
{

Connection::Connection(Owner parent, asio::io_context& context, 
	TSQueue<Ref<Message>>& messagesIn)
	: m_Context(context),
	m_MessagesIn(messagesIn),
	m_Socket(context)
{
	m_Owner = parent;
}

Connection::~Connection()
{
	if (m_Socket.is_open())
	{
		asio::error_code ec;
		m_Socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
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

void Connection::ConnectToClient(const uint32_t& id)
{
	if (m_Owner == Owner::Server)
	{
		if (m_Socket.is_open())
		{
			m_Id = id;
			StartRead();
		}
	}
}

void Connection::ConnectToServer(
	const asio::ip::tcp::resolver::results_type& endpoints)
{
	if (m_Owner == Owner::Client)
	{
		asio::async_connect(m_Socket, endpoints, 
			std::bind(&Connection::StartRead, this));
	}
}

void Connection::Disconnect()
{
	if (IsConnected())
	{
		asio::post(m_Context, [this]() { m_Socket.close(); });
	}
}

bool Connection::IsConnected() const
{
	return m_Socket.is_open();
}

void Connection::Send(Ref<Message> message)
{
	asio::post(m_Context, std::bind(&Connection::StartWrite, this,
		message));
}

void Connection::StartWrite(Ref<Message> message)
{
	bool writingMessages = !m_MessagesOut.empty();
	m_MessagesOut.push_back(message);
	if (!writingMessages)
	{
		SN_CORE_INFO("[Connection] Writing {}",
			message->GetMessageType());
		WriteMessage();
	}
}

void Connection::WriteMessage()
{
	// TODO: Separate message size and message encoding into separate
	// buffers.
	auto message = m_MessagesOut.pop_front();
	auto encoding = MessageEncoder::Encode(message);
	asio::async_write(m_Socket, asio::buffer(*encoding),
		std::bind(&Connection::OnWriteMessage, this,
		std::placeholders::_1));
}

void Connection::OnWriteMessage(const std::error_code& error)
{
	if (!error)
	{
		if (!m_MessagesOut.empty())
		{
			WriteMessage();
		}
	}
	else
	{
		SN_CORE_ERROR("[Connection {0}] Write Message Fail.", m_Id);
		m_Socket.close();
	}
}

void Connection::StartRead()
{
	// Set up buffer for new read.
	SN_CORE_ASSERT(m_Buffer == nullptr, "Buffer is not reset.");
	m_BufferSize = 0;
	m_Buffer = CreateRef<MessageEncoding>();

	asio::async_read(m_Socket, 
		asio::buffer(&m_BufferSize, sizeof(m_BufferSize)),
		std::bind(&Connection::ReadMessageSize, 
		this, std::placeholders::_1));
}

void Connection::ReadMessageSize(const std::error_code& error)
{
	SN_CORE_INFO("[Connection {0}] Reading message size.", m_Id);
	if (!error)
	{
		SN_CORE_ASSERT(m_Buffer, "Buffer is not allocated.");
		m_Buffer->resize(m_BufferSize);
		SN_CORE_INFO("[Connection {0}] Resized buffer {1}.", m_Id,
			m_BufferSize);
		asio::async_read(m_Socket, asio::buffer(*m_Buffer),
			std::bind(&Connection::ReadMessage, this,
			std::placeholders::_1));
	}
	else
	{
		SN_CORE_ERROR("[Connection] Error: {0}", error.message());
		m_Socket.close();
	}
}

void Connection::ReadMessage(const std::error_code& error)
{
	SN_CORE_INFO("[Connection {0}] Reading message.", m_Id);
	if (!error)
	{
		Ref<MessageEncoding> encoding = nullptr;
		std::swap(m_Buffer, encoding);
		auto message = MessageEncoder::Decode(encoding);
		
		AddToIncomingMessageQueue(message);
	}
	else
	{
		SN_CORE_ERROR("[Connection] Error: {0}", error.message());
	}
}

void Connection::AddToIncomingMessageQueue(Ref<Message> message)
{
	m_MessagesIn.push_back(message);
	StartRead();
}

}

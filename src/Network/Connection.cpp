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
			m_ID = id;
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
		WriteMessageSize();
	}
}

void Connection::WriteMessageSize()
{
}

void Connection::WriteMessage()
{
}

void Connection::StartRead()
{
	asio::async_read(m_Socket, 
		asio::buffer(&m_BufferSize, sizeof(m_BufferSize)),
		std::bind(&Connection::ReadMessageSize, 
		this, std::placeholders::_1));
}

void Connection::ReadMessageSize(const std::error_code& error)
{
	if (!error)
	{
		SN_CORE_ASSERT(m_Buffer, "Buffer is not reset.");
		m_Buffer->resize(m_BufferSize);
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
	if (!error)
	{
		auto message = MessageEncoder::Decode(m_Buffer);
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

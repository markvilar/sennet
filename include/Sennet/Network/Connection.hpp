#pragma once

#include "asio.hpp"

#include "Sennet/Network/Message.hpp"
#include "Sennet/Network/TSQueue.hpp"

namespace Sennet
{

// Forward declaration.
template <typename T>
class Server;

template <typename T> 
class Connection : public std::enable_shared_from_this<Connection<T>>
{
public:
	enum class Owner
	{
		Server,
		Client
	};

	Connection(Owner parent, 
		asio::io_context& context, 
		asio::ip::tcp::socket socket, 
		TSQueue<OwnedMessage<T>>& messagesIn)
		: m_Context(context), m_Socket(std::move(socket)),
		m_MessagesIn(messagesIn)
	{
		m_Owner = parent;

		if (m_Owner == Owner::Server)
		{
			m_HandshakeOut = uint64_t(
				std::chrono::system_clock::now()
				.time_since_epoch().count());
			m_HandshakeCheck = Scramble(m_HandshakeOut);
		}
		else
		{
			m_HandshakeOut = 0;
			m_HandshakeCheck = 0;
		}
	}

	virtual ~Connection()
	{
	}

	uint32_t GetID() const 
	{ 
		return m_ID; 
	}

	void ConnectToClient(Server<T>* server, const uint32_t& id = 0)
	{
		if (m_Owner == Owner::Server)
		{
			if (m_Socket.is_open())
			{
				m_ID = id;
				WriteValidation();
				ReadValidation(server);
			}
		}
	}

	void ConnectToServer(
		const asio::ip::tcp::resolver::results_type& endpoints)
	{
		if (m_Owner == Owner::Client)
		{
			asio::async_connect(m_Socket, endpoints,
				[this](std::error_code ec,
				asio::ip::tcp::endpoint endpoint)
				{
					if (!ec)
					{
						ReadValidation();
					}
				});
		}
	}

	void Disconnect()
	{
		if (IsConnected())
		{
			asio::post(m_Context, 
				[this]()
				{
					m_Socket.close();
				});
		}
	}

	bool IsConnected() const
	{
		return m_Socket.is_open();
	}

public: 
	void Send(const Message<T>& message)
	{
		asio::post(m_Context, 
			[this, message]()
			{
				bool writingMessages = !m_MessagesOut.empty();
				m_MessagesOut.push_back(message);
				if (!writingMessages)
				{
					WriteHeader();
				}
			});
	}

private:
	// ASYNC.
	void ReadHeader()
	{
		asio::async_read(m_Socket, 
			asio::buffer(&m_MessageTemporaryIn.Header,
			sizeof(MessageHeader<T>)),
			[this](std::error_code ec, uint64_t length)
			{
				if (!ec)
				{
					if (m_MessageTemporaryIn.Header.Size > 0)
					{
						m_MessageTemporaryIn.Body.resize(
							m_MessageTemporaryIn.
							Header.Size
							);
						ReadBody();
					}
					else
					{
						AddToIncomingMessageQueue();
					}
				}
				else
				{
					SN_CORE_ERROR("[{0}] Read Header Fail.",
						m_ID);
					m_Socket.close();
				}
			});
	}

	// ASYNC.
	void ReadBody()
	{
		asio::async_read(m_Socket,
			asio::buffer(m_MessageTemporaryIn.Body.data(), 
			m_MessageTemporaryIn.Body.size()),
			[this](std::error_code ec, uint64_t length)
			{
				if (!ec)
				{
					AddToIncomingMessageQueue();
				}
				else
				{
					SN_CORE_ERROR("[{0}] Read Body Fail.",
						m_ID);
					m_Socket.close();
				}
			});
	}

	// ASYNC.
	void WriteHeader()
	{
		asio::async_write(m_Socket, 
			asio::buffer(&m_MessagesOut.front().Header,
			sizeof(MessageHeader<T>)),
			[this](std::error_code ec, uint64_t length)
			{
				if (!ec)
				{
					if (m_MessagesOut.front().Body.size() >
						0)
					{
						WriteBody();
					}
					else
					{
						m_MessagesOut.pop_front();
						if (!m_MessagesOut.empty())
						{
							WriteHeader();
						}
					}
				}
				else
				{
					SN_CORE_ERROR("[{0}] Write Header "
						"Fail.", ec.message());
					m_Socket.close();
				}
			});
	}

	// ASYNC.
	void WriteBody()
	{
		asio::async_write(m_Socket,
			asio::buffer(m_MessagesOut.front().Body.data(),
			m_MessagesOut.front().Body.size()),
			[this](std::error_code ec, uint64_t length)
			{
				if (!ec)
				{
					m_MessagesOut.pop_front();

					if (!m_MessagesOut.empty())
					{
						
						WriteHeader();
					}
				}
				else
				{
					SN_CORE_ERROR("[{0}] Write Body Fail.",
						m_ID);
					m_Socket.close();
				}
			});
	}

	void AddToIncomingMessageQueue()
	{
		if (m_Owner == Owner::Server)
		{
			m_MessagesIn.push_back({ this->shared_from_this(),
				m_MessageTemporaryIn });
		}
		else
		{
			m_MessagesIn.push_back({ nullptr, 
				m_MessageTemporaryIn });
		}

		ReadHeader();
	}

	uint64_t Scramble(const uint64_t input)
	{
		uint64_t output = input ^ 0xDEADBEEFC0DECAFE;
		output = (output & 0xF0F0F0F0F0F0F0) >> 4 
			| (output & 0xF0F0F0F0F0F0F0) << 4;
		return output ^ 0xC0DEFACE12345678;
	}

	void WriteValidation()
	{
		asio::async_write(m_Socket, 
			asio::buffer(&m_HandshakeOut, sizeof(m_HandshakeOut)), 
			[this](std::error_code ec, uint64_t length)
			{
				if (!ec)
				{
					if (m_Owner == Owner::Client)
					{
						ReadHeader();
					}
				}
				else
				{
					m_Socket.close();
				}
			});
	}
	
	void ReadValidation(Server<T>* server = nullptr)
	{
		asio::async_read(m_Socket, 
			asio::buffer(&m_HandshakeIn, sizeof(m_HandshakeIn)),
			[this, server](std::error_code ec, uint64_t length)
			{
				if (ec)
				{
					SN_CORE_WARN("Client Disconnected "
						"(ReadValidation).");
					m_Socket.close();
					return;
				}
				
				if (m_Owner == Owner::Server)
				{
					if (m_HandshakeIn == m_HandshakeCheck)
					{
						SN_CORE_INFO("Client "
							"Validated.");
						server->OnClientValidated(this
							->shared_from_this());

						ReadHeader();
					}
					else
					{
						SN_CORE_WARN("Client "
							"Disconnected (Fail "
							"Validation).");
						m_Socket.close();
					}
				}
				else
				{
					m_HandshakeOut = Scramble(
						m_HandshakeIn);
					WriteValidation();
				}
			});
	}

protected:
	// Temporary.
	asio::ip::tcp::socket m_Socket;
	asio::io_context& m_Context;

	Owner m_Owner = Owner::Server;
	uint32_t m_ID = 0;

	// Outgoing message queue owned by connection.
	TSQueue<Message<T>> m_MessagesOut;
	
	// Incoming message queue provided by client/server.
	TSQueue<OwnedMessage<T>>& m_MessagesIn;

	// Message used to temporarily store incoming messages.
	Message<T> m_MessageTemporaryIn;

	// Handshake validation.
	uint64_t m_HandshakeOut = 0;
	uint64_t m_HandshakeIn = 0;
	uint64_t m_HandshakeCheck = 0;
};

}

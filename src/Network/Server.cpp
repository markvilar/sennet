#include "Sennet/pch.hpp"

#include "Sennet/Network/Server.hpp"

namespace Sennet
{

Server* Server::s_Instance = nullptr;

Server::Server(uint16_t port)
	: m_Acceptor(m_Context, 
	asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
	SN_CORE_ASSERT(!s_Instance, "Server already exists!");
	s_Instance = this;
}

Server::~Server()
{
	Stop();
}

bool Server::Start()
{
	try
	{
		AsyncAccept();
		m_ContextThread = std::thread(
			[this]() 
			{ 
				m_Context.run(); 
				SN_CORE_INFO("[Server] Context done!");
				return;
			});
	}
	catch (std::exception& e)
	{
		SN_CORE_ERROR("[Server] Exception: {}", e.what());
		return false;
	}
	
	SN_CORE_INFO("[Server] Started!");
	return true;
}

void Server::Stop()
{
	m_Context.stop();

	if (m_ContextThread.joinable())
	{
		SN_CORE_INFO("[Server] Joining context thread.");
		m_ContextThread.join();
	}

	SN_CORE_INFO("[Server] Stopped!");
}

void Server::MessageClient(Ref<Connection> client, Ref<Message> message)
{
	if (client && client->IsConnected())
	{
		client->Send(message);
	}
	else
	{
		OnClientDisconnect(client);
		client.reset();
	}
}

void Server::MessageAllClients(Ref<Message> message)
{
	bool hasInvalidClients = false;
	for (auto client : m_Connections)
	{
		if (client && client->IsConnected())
		{
			client->Send(message);
		}
		else
		{
			OnClientDisconnect(client);
			client.reset();
			hasInvalidClients = true;
		}
	}

	if (hasInvalidClients)
	{
		m_Connections.erase(std::remove(m_Connections.begin(), 
			m_Connections.end(), nullptr));
	}
}

void Server::Update(uint64_t maxMessages)
{
	uint64_t messageCount = 0;
	while (messageCount < maxMessages && !m_InQueue.empty())
	{
		auto message = m_InQueue.pop_front();

		// TODO: Fix message remote.
		OnMessage(nullptr, message);
	}
}

bool Server::OnClientConnect(Ref<Connection> client)
{
	return false;
}

void Server::OnClientDisconnect(Ref<Connection> client)
{
}

void Server::OnMessage(Ref<Connection> client, Ref<Message> message)
{
}

void Server::AsyncAccept()
{
	Ref<Connection> connection = CreateRef<Connection>(
		Connection::Owner::Server, m_Context, m_InQueue);
	m_Acceptor.async_accept(connection->GetSocket(),
		std::bind(&Server::OnAccept, this, std::placeholders::_1,
		connection));
}

void Server::OnAccept(const std::error_code& error, Ref<Connection> connection)
{
	if (!error)
	{
		SN_CORE_INFO("[Server] New connection: {0}", 
			connection->GetRemoteEndpoint());

		if (OnClientConnect(connection))
		{
			m_Connections.push_back(std::move(connection));
			m_Connections.back()->ConnectToClient(m_IDCounter++);
			SN_CORE_INFO("[Server] Connection accepted!");
		}
		else
		{
			SN_CORE_INFO("[Server] Connection rejected!");
		}
	}
	else
	{
		SN_CORE_ERROR("[Server] Accept Error: {0}", error.message());
	}

	AsyncAccept();
}

}

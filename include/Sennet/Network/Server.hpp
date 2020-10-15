#pragma once

// Temporary.
#include "asio.hpp"

#include "Sennet/Messages/Message.hpp"

#include "Sennet/Network/Connection.hpp"
#include "Sennet/Network/Endpoint.hpp"
#include "Sennet/Network/TSMap.hpp"
#include "Sennet/Network/TSQueue.hpp"

namespace Sennet
{

class Server
{
	// Server class interface.

public:
	Server(uint16_t port);
	virtual ~Server();

	bool Start();
	void Stop();

	void MessageClient(Ref<Connection> client, Ref<Message> message);
	void MessageAllClients(Ref<Message> message);

	void Update(uint64_t maxMessages = -1);

	static Server& Get() { return *s_Instance; }

protected:
	virtual bool OnClientConnect(Ref<Connection> client);
	virtual void OnClientDisconnect(Ref<Connection> client);
	virtual void OnMessage(Ref<Connection> client, Ref<Message> message);

private:
	void AsyncAccept();
	void OnAccept(const std::error_code& error, Ref<Connection> client);

private:
	TSQueue<Ref<Message>> m_InQueue;
	std::deque<Ref<Connection>> m_Connections;
	uint32_t m_IDCounter = 10000;

	// Temporary.
	asio::io_context m_Context;
	std::thread m_ContextThread;

	// Temporary.
	asio::ip::tcp::acceptor m_Acceptor;

private:
	static Server* s_Instance;

};

}

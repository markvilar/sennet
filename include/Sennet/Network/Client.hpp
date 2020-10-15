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

class Client
{
public:
	Client() ;
	virtual ~Client();

	bool Connect(const std::string& host, const uint16_t& port);
	void Disconnect();
	bool IsConnected();

	void Send(const Ref<Message>& message);
	TSQueue<Ref<Message>>& Incoming() { return m_MessagesIn; };

private:
	Scope<Connection> m_Connection;

	// Temporary.
	asio::io_context m_Context;
	std::thread m_ContextThread;

	TSQueue<Ref<Message>> m_MessagesIn;
};

}

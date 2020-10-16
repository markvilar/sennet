#pragma once

#include "asio.hpp"

#include "Sennet/Core/Base.hpp"
#include "Sennet/Messages/Message.hpp"
#include "Sennet/Network/TSQueue.hpp"

namespace Sennet
{

class Connection : public std::enable_shared_from_this<Connection>
{
	typedef std::function<void(Ref<MessageEncoding>)> DataCallbackFn;

public:
	enum class Owner
	{
		Server,
		Client
	};

	Connection(Owner parent, asio::io_context& context, 
		TSQueue<Ref<Message>>& messagesIn);
	virtual ~Connection();

	// Temporary.
	asio::ip::tcp::socket& GetSocket();
	asio::ip::tcp::endpoint GetRemoteEndpoint() const;
	asio::ip::tcp::endpoint GetLocalEndpoint() const;

	uint32_t GetID() const;

	void ConnectToClient(const uint32_t& id = 0);
	void ConnectToServer(
		const asio::ip::tcp::resolver::results_type& endpoints);
	void Disconnect();
	bool IsConnected() const;

	void Send(Ref<Message> message);

private:
	void StartWrite(Ref<Message> message);
	void WriteMessage();
	void OnWriteMessage(const std::error_code& error);

	void StartRead();
	void ReadMessageSize(const std::error_code& error);
	void ReadMessage(const std::error_code& error);
	void AddToIncomingMessageQueue(Ref<Message> message);

private:
	// Temporary.
	asio::ip::tcp::socket m_Socket;
	asio::io_context& m_Context;

	Owner m_Owner = Owner::Server;
	uint32_t m_Id = 0;

	uint64_t m_BufferSize = 0;
	Ref<MessageEncoding> m_Buffer = nullptr;

	TSQueue<Ref<Message>> m_MessagesOut;
	TSQueue<Ref<Message>>& m_MessagesIn;
};

}

#pragma once
#include <Sennet/pch.hpp>

#include <boost/asio.hpp>

#include <Sennet/Core/Base.hpp>

#include <Sennet/Messages/Message.hpp>

#include <Sennet/Network/Connection.hpp>

namespace Sennet 
{

class ConnectionManager
{
public:
	using MessageCallbackFn= std::function<void(Ref<Message>&)>;

	ConnectionManager(unsigned short port, uint64_t wait_for = 1);
	~ConnectionManager();
	
	boost::asio::io_service& GetIOService();

	std::queue<Ref<MessageEncoding>>& GetInboundQueue();
	std::queue<std::pair<Ref<Connection>, Ref<Message>>>& GetOutboundQueue();
	std::map<boost::asio::ip::tcp::endpoint, Ref<Connection>>& GetConnections();
	
	void SetMessageCallback(const MessageCallbackFn& callback);
		
	void Start();
	void Stop();
	void Run();

	Ref<Connection> Connect(std::string host, std::string port);
	Ref<Connection> ConnectionSearch(const std::string& addr, 
		const unsigned short port);
	void PushMessage(Ref<Connection> conn, const Message& msg);

	void OnData(Ref<MessageEncoding> rawMsg);

	void AsyncAccept();
	void OnAccept(const boost::system::error_code& error, 
		Ref<Connection> conn);

private:
	void ExecutionLoop();

private:
	boost::asio::io_service m_IOService;
	boost::asio::ip::tcp::acceptor m_Acceptor;

	std::queue<std::pair<Ref<Connection>, Ref<Message>>> m_OutboundQueue;
	std::queue<Ref<MessageEncoding>> m_InboundQueue;
	std::map<boost::asio::ip::tcp::endpoint, Ref<Connection>> m_Connections;

	std::atomic<bool> m_StopFlag;
	std::thread m_ExecutionThread;
	std::mutex m_Mutex;

	uint64_t m_WaitFor;
	
	MessageCallbackFn m_MessageCallback;
};

}

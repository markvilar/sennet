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
	typedef std::pair<std::string, unsigned short> EndpointData;
public:
	using MessageCallbackFn= std::function<void(Ref<Message>&)>;

	ConnectionManager(unsigned short port, uint64_t waitFor = 1);
	~ConnectionManager();
	
	Ref<std::vector<EndpointData>> GetLocalEndpointsData();
	Ref<std::vector<EndpointData>> GetRemoteEndpointsData();
	
	void SetMessageCallback(const MessageCallbackFn& callback);
		
	void Start();
	void Stop();

	Ref<Connection> Connect(std::string host, std::string port);
	Ref<Connection> FindConnection(const std::string& addr, 
		const unsigned short port);
	void SubmitMessage(Ref<Connection> conn, Ref<Message> msg);

	void OnData(Ref<MessageEncoding> rawMsg);

	void AsyncAccept();
	void OnAccept(const boost::system::error_code& error, 
		Ref<Connection> conn);

private:
	void IOWorker();
	void ExecutionWorker();

private:
	boost::asio::io_service m_IOService;
	boost::asio::ip::tcp::acceptor m_Acceptor;

	std::queue<std::pair<Ref<Connection>, Ref<Message>>> m_OutQueue;
	std::queue<Ref<MessageEncoding>> m_InQueue;
	std::map<boost::asio::ip::tcp::endpoint, Ref<Connection>> m_Connections;

	std::thread m_ExecutionThread;
	std::thread m_IOThread;

	std::atomic<bool> m_StopFlag;
	std::mutex m_InQueueMutex;
	std::mutex m_OutQueueMutex;
	std::mutex m_ConnectionsMutex;

	uint64_t m_WaitFor;
	
	MessageCallbackFn m_MessageCallback;
};

}

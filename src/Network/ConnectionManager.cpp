#include <Sennet/Network/ConnectionManager.hpp>

namespace Sennet 
{

ConnectionManager::ConnectionManager(unsigned short port, uint64_t waitFor)
	: m_IOService(),
	m_Acceptor(m_IOService, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::tcp::v4(), port)),
	m_Connections(),
	m_ExecutionThread(),
	m_InboundQueue(),
	m_OutboundQueue(),
	m_StopFlag(false),
	m_WaitFor(waitFor)
{
	SN_CORE_ASSERT(waitFor > 0, "[ConnectionManager] Not waiting for \
		clients!");
}

ConnectionManager::~ConnectionManager()
{ 
	Stop(); 
}

boost::asio::io_service& ConnectionManager::GetIOService() 
{ 
	return m_IOService; 
}

std::queue<Ref<MessageEncoding>>& ConnectionManager::GetInboundQueue()
{ 
	return m_InboundQueue;
}

std::queue<std::pair<Ref<Connection>, Ref<Message>>>& 
	ConnectionManager::GetOutboundQueue()
{
	return m_OutboundQueue;
}

std::map<boost::asio::ip::tcp::endpoint, Ref<Connection>>& 
	ConnectionManager::GetConnections()
{
	return m_Connections;
}

void ConnectionManager::SetMessageCallback(const MessageCallbackFn& callback)
{
	m_MessageCallback = callback;
}

void ConnectionManager::Start()
{
	m_Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_Acceptor.set_option(boost::asio::ip::tcp::acceptor::linger(true, 0));

	m_IOThread = std::thread(std::bind(&ConnectionManager::IOWorker, this));

	m_ExecutionThread = std::thread(
		std::bind(&ConnectionManager::ExecutionWorker, this));
	
	AsyncAccept();
}

void ConnectionManager::Stop()
{
	m_StopFlag = true;
	m_IOService.stop();

	if (m_IOThread.joinable())
	{
		m_IOThread.join();
		SN_CORE_TRACE("[ConnectionManager] Joined IO thread.");
	}
}

Ref<Connection> ConnectionManager::Connect(std::string host, std::string port)
{
	boost::asio::ip::tcp::resolver resolver(m_IOService);
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(),
		host, port);
	
	boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
	boost::asio::ip::tcp::resolver::iterator end;

	for (boost::asio::ip::tcp::resolver::iterator i = it; i != end; ++i)
		// If the ConnectionManager already has a Connection 
		// established with the endpoint.
		if (m_Connections.count(*i) != 0)
			return m_Connections[*i];

	auto connection = CreateRef<Connection>(GetIOService());

	// TODO: Look into adding a more general Connection timer!
	for (uint64_t i = 0; i < 64; ++i)
	{
		boost::system::error_code ec;
		boost::asio::connect(connection->GetSocket(), it, ec);
		if (!ec) break;

		std::chrono::milliseconds period(100);
		std::this_thread::sleep_for(period);
	}

	connection->GetSocket().set_option(
		boost::asio::ip::tcp::socket::reuse_address(true));
	connection->GetSocket().set_option(
		boost::asio::ip::tcp::socket::linger(true, 0));
		
	boost::asio::ip::tcp::endpoint ep = connection->GetRemoteEndpoint();
	SN_CORE_ASSERT(m_Connections.count(ep) == 0, 
		"[ConnectionManager] Connection already established!");

	SN_CORE_TRACE("[ConnectionManager] Added connection {0}:{1}.", 
		ep.address().to_string(), ep.port());
	m_Connections[ep] = connection;

	connection->AsyncRead();

	return connection;
}

Ref<Connection> ConnectionManager::ConnectionSearch(const std::string& addr,
	const unsigned short port)
{
	auto connections = GetConnections();
	auto it = connections.begin();
	while (it != connections.end())
	{
		if (it->first.address().to_string() == addr and 
			it->first.port() == port)
			return it->second;
		++it;
	}
	return nullptr;
}

void ConnectionManager::PushMessage(Ref<Connection> connection, Ref<Message> msg)
{
	m_Mutex.lock();
	m_OutboundQueue.push(std::make_pair(connection, msg));
	m_Mutex.unlock();
}

void ConnectionManager::OnData(Ref<MessageEncoding> rawMsg)
{
	m_Mutex.lock();
	m_InboundQueue.push(rawMsg);
	m_Mutex.unlock();
}

void ConnectionManager::AsyncAccept()
{
	Ref<Connection> connection = CreateRef<Connection>(GetIOService());

	m_Acceptor.async_accept(connection->GetSocket(),
		std::bind(&ConnectionManager::OnAccept, this,
		std::placeholders::_1, connection));
		
}

void ConnectionManager::OnAccept(boost::system::error_code const& error,
	Ref<Connection> connection)
{
	if (!error)
	{
		Ref<Connection> oldConnection = connection;
		connection.reset(new Connection(GetIOService()));

		m_Acceptor.async_accept(connection->GetSocket(),
			std::bind(&ConnectionManager::OnAccept, this,
			std::placeholders::_1, connection));
				
		boost::asio::ip::tcp::endpoint ep =
			oldConnection->GetRemoteEndpoint();

		SN_CORE_ASSERT(m_Connections.count(ep) == 0, 
			"[ConnectionManager] Connection already established!");

		oldConnection->SetDataCallback(
			std::bind(&ConnectionManager::OnData, this, 
			std::placeholders::_1));
			
		m_Connections[ep] = oldConnection;

		SN_CORE_TRACE("[ConnectionManager] Accepted connection {0}:{1}.",
			ep.address().to_string(), ep.port());

		oldConnection->AsyncRead();
	}
}

void ConnectionManager::IOWorker()
{
	SN_CORE_TRACE("[ConnectionManager] Started IO thread.");

	boost::asio::io_service::work work(m_IOService);
	m_IOService.run();

	if (m_ExecutionThread.joinable())
	{
		m_ExecutionThread.join();
		SN_CORE_TRACE("[ConnectionManager] Joined execution thread.");
	}
}

void ConnectionManager::ExecutionWorker()
{
	SN_CORE_TRACE("[ConnectionManager] Started execution thread.");
	while (!m_StopFlag)
	{
		if (!m_OutboundQueue.empty())
		{
			auto [connection, outboundMsg] = m_OutboundQueue.front();
			m_OutboundQueue.pop();

			SN_CORE_ASSERT(connection, "[ConnectionManager] \
				Connection is null!");
			SN_CORE_ASSERT(outboundMsg, "[ConnectionManager] \
				Message is null!");
			
			auto outboundParcel = MessageEncoder::Encode(outboundMsg);
				
			connection->AsyncWrite(outboundParcel);
		}

		if (!m_InboundQueue.empty())
		{
			auto inboundParcel = m_InboundQueue.front();
			m_InboundQueue.pop();

			SN_CORE_ASSERT(inboundParcel, 
				"[ConnectionManager] Inbound parcel is null!");

			auto inboundMsg = MessageEncoder::Decode(inboundParcel);

			if (m_MessageCallback && inboundMsg)
			{
				m_MessageCallback(inboundMsg);
			}
			else if (!m_MessageCallback)
			{
				SN_CORE_WARN("[ConnectionManager] No message \
					callback bound.");
			}
			else if (!inboundMsg)
			{
				SN_CORE_WARN("[ConnectionManager] Inbound \
					message is null.");
			}
		}
	}
}

}

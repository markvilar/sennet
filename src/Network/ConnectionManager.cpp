#include <Sennet/Network/ConnectionManager.hpp>

namespace Sennet 
{

ConnectionManager* ConnectionManager::s_Instance = nullptr;

ConnectionManager::ConnectionManager(unsigned short port, uint64_t waitFor)
	: m_IOService(),
	m_Acceptor(m_IOService, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::tcp::v4(), port)),
	m_Connections(),
	m_ExecutionThread(),
	m_InQueue(),
	m_OutQueue(),
	m_StopFlag(false),
	m_WaitFor(waitFor)
{
	SN_CORE_ASSERT(!s_Instance, "Connection Manager already exists!");
	s_Instance = this;
	SN_CORE_ASSERT(waitFor > 0, "Not waiting for clients!");
}

ConnectionManager::~ConnectionManager()
{ 
	Stop(); 
}

Ref<std::vector<ConnectionManager::EndpointData>> 
	ConnectionManager::GetLocalEndpointsData()
{
	std::lock_guard<std::mutex> lock(m_ConnectionsMutex);
	auto data = CreateRef<std::vector<ConnectionManager::EndpointData>>(
		m_Connections.size());
	int connectionIndex = 0;
	for (auto& connection : m_Connections)
	{
		data->at(connectionIndex++) = 
			connection.second->GetLocalInformation();
	}
	return data;
}

Ref<std::vector<ConnectionManager::EndpointData>> 
	ConnectionManager::GetRemoteEndpointsData()
{
	std::lock_guard<std::mutex> lock(m_ConnectionsMutex);
	auto data = CreateRef<std::vector<ConnectionManager::EndpointData>>(
		m_Connections.size());
	int connectionIndex = 0;
	for (auto& connection : m_Connections)
	{
		data->at(connectionIndex++) = 
			connection.second->GetRemoteInformation();
	}
	return data;
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
		SN_CORE_TRACE("Joined IO thread.");
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

	auto connection = CreateRef<Connection>(m_IOService);

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
		"Connection already established!");

	connection->SetDataCallback(
		std::bind(&ConnectionManager::OnData, this, 
		std::placeholders::_1));

	SN_CORE_TRACE("Added connection {0}:{1}.", 
		ep.address().to_string(), ep.port());
	m_Connections[ep] = connection;

	connection->AsyncRead();

	return connection;
}

Ref<Connection> ConnectionManager::FindConnection(const std::string& addr,
	const unsigned short port)
{
	std::lock_guard<std::mutex> lock(m_ConnectionsMutex);
	auto it = m_Connections.begin();
	while (it != m_Connections.end())
	{
		if (it->first.address().to_string() == addr and 
			it->first.port() == port)
			return it->second;
		++it;
	}
	return nullptr;
}

void ConnectionManager::SubmitMessage(Ref<Connection> connection, Ref<Message> msg)
{
	std::lock_guard<std::mutex> lock(m_OutQueueMutex);
	m_OutQueue.push(std::make_pair(connection, msg));
}

void ConnectionManager::OnData(Ref<MessageEncoding> rawMsg)
{
	std::lock_guard<std::mutex> lock(m_InQueueMutex);
	m_InQueue.push(rawMsg);
}

void ConnectionManager::AsyncAccept()
{
	Ref<Connection> connection = CreateRef<Connection>(m_IOService);
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
		connection.reset(new Connection(m_IOService));

		m_Acceptor.async_accept(connection->GetSocket(),
			std::bind(&ConnectionManager::OnAccept, this,
			std::placeholders::_1, connection));
				
		boost::asio::ip::tcp::endpoint ep =
			oldConnection->GetRemoteEndpoint();

		m_ConnectionsMutex.lock();
		SN_CORE_ASSERT(m_Connections.count(ep) == 0, 
			"Connection already established!");
		oldConnection->SetDataCallback(
			std::bind(&ConnectionManager::OnData, this, 
			std::placeholders::_1));
		m_Connections[ep] = oldConnection;
		m_ConnectionsMutex.unlock();

		SN_CORE_TRACE("Accepted connection {0}:{1}.", 
			ep.address().to_string(), ep.port());

		oldConnection->AsyncRead();
	}
}

void ConnectionManager::IOWorker()
{
	SN_CORE_TRACE("Started IO thread.");

	boost::asio::io_service::work work(m_IOService);
	m_IOService.run();

	if (m_ExecutionThread.joinable())
	{
		m_ExecutionThread.join();
		SN_CORE_TRACE("Joined message processing thread.");
	}
}

void ConnectionManager::ExecutionWorker()
{
	SN_CORE_TRACE("Started message processing thread.");
	while (!m_StopFlag)
	{
		m_OutQueueMutex.lock();
		if (!m_OutQueue.empty())
		{
			auto [connection, outMsg] = m_OutQueue.front();
			m_OutQueue.pop();

			SN_CORE_ASSERT(connection, "Invalid connection!");
			SN_CORE_ASSERT(outMsg, "Invalid outbound message!");
			
			auto outParcel = MessageEncoder::Encode(outMsg);
			connection->AsyncWrite(outParcel);
		}
		m_OutQueueMutex.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(
			m_ExecutionTimeout));

		m_InQueueMutex.lock();
		if (!m_InQueue.empty())
		{
			auto inParcel = m_InQueue.front();
			m_InQueue.pop();

			SN_CORE_ASSERT(inParcel, "Invalid inbound parcel!");

			auto inMsg = MessageEncoder::Decode(inParcel);

			if (m_MessageCallback && inMsg)
			{
				m_MessageCallback(inMsg);
			}
			else if (!m_MessageCallback)
			{
				SN_CORE_WARN("No message callback bound.");
			}
		}
		m_InQueueMutex.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(
			m_ExecutionTimeout));
	}
}

}

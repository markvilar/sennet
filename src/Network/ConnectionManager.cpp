#include <Sennet/Network/ConnectionManager.hpp>

#include <boost/lexical_cast.hpp>

#include <Sennet/Core/Base.hpp>
#include <Sennet/Messages/MessageEncoder.hpp>

namespace Sennet 
{

ConnectionManager::ConnectionManager(std::string port, uint64_t waitFor)
	: m_IOService(),
	m_Acceptor(m_IOService, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::tcp::v4(), 
		boost::lexical_cast<boost::uint16_t>(port))),
	m_Connections(),
	m_ExecutionThread(),
	m_InboundQueue(),
	m_OutboundQueue(),
	m_StopFlag(false),
	m_WaitFor(waitFor)
{
	// Make sure we are waiting for some clients.
	SN_CORE_ASSERT(waitFor != 0, "Not waiting for clients!");
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
	// Set up acceptor. 
	// 	- Option 'reuse_address' allows the socket to be bound to an
	// 		address that is already in use.
	// 	- Option 'linger' specifies if socket should linger on close if
	// 		unsent data is present.
	m_Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_Acceptor.set_option(boost::asio::ip::tcp::acceptor::linger(true, 0));

	// Start execution thread.
	m_ExecutionThread = std::thread(
		std::bind(&ConnectionManager::ExecutionLoop, this));
	
	// Start accepting Connections.
	AsyncAccept();
}

void ConnectionManager::Stop()
{
	// Tell the execution thread to stop.
	m_StopFlag = true;

	// Destroy the keep-alive work object, which will cause run() to return
	// when all I/O work is done.
	m_IOService.stop();
}

void ConnectionManager::Run()
{
	// Keep io_service::run() from returning.
	boost::asio::io_service::work work(m_IOService);

	m_IOService.run();

	if (m_ExecutionThread.joinable())
		SN_CORE_TRACE("Joining execution thread.");
		m_ExecutionThread.join();
}

Ref<Connection> ConnectionManager::Connect(std::string host, std::string port)
{
	// Set up resolver and query.
	boost::asio::ip::tcp::resolver resolver(m_IOService);
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(),
		host, port);
	
	// Initialize iterators.
	boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
	boost::asio::ip::tcp::resolver::iterator end;

	// Iterate over list of entries from resolving the query.
	for (boost::asio::ip::tcp::resolver::iterator i = it; i != end; ++i)
		// If the ConnectionManager already has a Connection 
		// established with the endpoint.
		if (m_Connections.count(*i) != 0)
			return m_Connections[*i];

	// If there are no existing Connections to host, initialize new 
	// Connection.
	auto connection = CreateRef<Connection>(GetIOService());

	// Wait for some time for the Connection manager to become available.
	// TODO: Look into adding a more general Connection timer!
	for (uint64_t i = 0; i < 64; ++i)
	{
		boost::system::error_code ec;
		boost::asio::connect(connection->GetSocket(), it, ec);
		if (!ec) break;

		// Otherwise, sleep and try again.
		std::chrono::milliseconds period(100);
		std::this_thread::sleep_for(period);
	}

	// Set Connection socket options. 
	// 	- Option 'reuse_address' allows the socket to be bound to an
	// 		address that is already in use.
	// 	- Option 'linger' specifies if socket should linger on close if
	// 		unsent data is present.
	connection->GetSocket().set_option(
		boost::asio::ip::tcp::socket::reuse_address(true));
	connection->GetSocket().set_option(
		boost::asio::ip::tcp::socket::linger(true, 0));
		
	// Note that if there were multiple I/O threads, one would have to lock
	// before accessing the Connection map.
	boost::asio::ip::tcp::endpoint ep = connection->GetRemoteEndpoint();
	SN_CORE_ASSERT(m_Connections.count(ep) == 0, 
		"Connection already established!");

	SN_CORE_TRACE("Added new Connection: {0}:{1}", ep.address().to_string(),
		ep.port());
	m_Connections[ep] = connection;

	// Start the Connection by calling the async. read operation.
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

void ConnectionManager::PushMessage(Ref<Connection> connection, const Message& msg)
{
	Ref<Message> msgPtr(msg.Clone());

	m_Mutex.lock();
	m_OutboundQueue.push(std::make_pair(connection, msgPtr));
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

	// Set up async. accept operation with handle_accept() as completion
	// handler.
	m_Acceptor.async_accept(connection->GetSocket(),
		std::bind(&ConnectionManager::OnAccept, this,
		std::placeholders::_1, connection));
		
}

void ConnectionManager::OnAccept(boost::system::error_code const& error,
	Ref<Connection> connection)
{
	if (!error)
	{
		// If there was no error, then we need to insert conn into the
		// Connection table, but first the next async_accept() is set
		// up.
		Ref<Connection> oldConnection = connection;

		// Initialize new Connection.
		connection.reset(new Connection(GetIOService()));

		// Set up new async. accept operation with handle_accept() as
		// completion handler.
		m_Acceptor.async_accept(connection->GetSocket(),
			std::bind(&ConnectionManager::OnAccept, this,
			std::placeholders::_1, connection));
				
		
		// Note that if there were multiple I/O threads, we would have
		// to lock before touching the map.
		boost::asio::ip::tcp::endpoint ep =
			oldConnection->GetRemoteEndpoint();
		SN_CORE_ASSERT(m_Connections.count(ep) == 0, 
			"Connection already established!");

		oldConnection->SetDataCallback(
			std::bind(&ConnectionManager::OnData, this, 
			std::placeholders::_1));
			
		m_Connections[ep] = oldConnection;

		// Start read from the accepted Connection.
		oldConnection->AsyncRead();
	}
}

void ConnectionManager::ExecutionLoop()
{
	while (!m_StopFlag)
	{
		// TODO: Clean up!

		// Look for pending actions that has been posted locally to 
		// execute.
		if (!m_OutboundQueue.empty())
		{
			auto [connection, outboundMsg] = m_OutboundQueue.front();
			m_OutboundQueue.pop();

			SN_CORE_ASSERT(connection, "Connection is null!");
			SN_CORE_ASSERT(outboundMsg, "Message is null!");
			
			auto outboundParcel = MessageEncoder::Encode(outboundMsg);
				
			connection->AsyncWrite(outboundParcel);
		}

		// If there's no pending outbound messages, find parcel to 
		// deserialize and execute.
		if (!m_InboundQueue.empty())
		{
			auto inboundParcel = m_InboundQueue.front();
			m_InboundQueue.pop();

			SN_CORE_ASSERT(inboundParcel, "Inbound parcel is null!");

			auto inboundMsg = MessageEncoder::Decode(inboundParcel);

			if (m_MessageCallback && inboundMsg)
			{
				m_MessageCallback(inboundMsg);
			}
			else if (!m_MessageCallback)
			{
				SN_CORE_WARN("In execution loop: No message \
					callback.");
			}
			else if (!inboundMsg)
			{
				SN_CORE_WARN("In execution loop: Message is \
					null.");
			}
		}
	}
}

}

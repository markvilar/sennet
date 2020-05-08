#include <zedutils/network.hpp>

namespace zed { namespace net {

//-------------------------------------------------------------------------------

void Service::on_request_received(const boost::system::error_code& ec,
	std::size_t bytes)
{
	// Check for errors
	if (ec)
	{
		std::cout << "[" << std::this_thread::get_id() 
			<< "][" << __FUNCTION__ << "][ERROR] Error code: " 
			<< ec.value() << ". Message: " << ec.message() << "\n";
		on_finish();
		return;
	}
	
	// Process request
	m_response = process_request(m_request);
	
	// Start async. write operation
	boost::asio::async_write(*m_socket.get(),
		boost::asio::buffer(m_response),
		[this](const boost::system::error_code& ec, std::size_t bytes)
		{
			on_response_sent(ec, bytes);
		});
}

void Service::on_response_sent(const boost::system::error_code& ec, 
std::size_t bytes)
{
	if (ec)
	{
		std::cout << "[" << std::this_thread::get_id() 
			<< "][" << __FUNCTION__ << "][ERROR] Error code: " 
			<< ec.value() << ". Message: " << ec.message() << "\n";
		on_finish();
		return;
	}
}

void Service::on_finish()
{
	delete this;
}

std::string Service::process_request(boost::asio::streambuf& request)
{
	// Emulate CPU-consuming operation
	int i = 0;
	while(i != 1000000)
	{
 		i++;
	}

	// Emulate thread blocking operation
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// Prepare and return reponse message
	std::string response = "Response\n";
	return response;
}

Service::Service(std::shared_ptr<boost::asio::ip::tcp::socket> socket) 
	: m_socket(socket)
{
}

Service::~Service()
{
}

void Service::start_handling()
{
	// Starts async. read operation. Reads into the m_request streambuf, 
	// until '\n' is read.
	boost::asio::async_read_until(*m_socket.get(), m_request, '\n',
		[this](const boost::system::error_code& ec, std::size_t bytes)
		{
			on_request_received(ec, bytes);
		});
}

//-------------------------------------------------------------------------------

void Acceptor::init_accept()
{
	// Create socket for new connection
	std::shared_ptr<boost::asio::ip::tcp::socket> socket(
		new boost::asio::ip::tcp::socket(m_ios));

	// Start async. accept operation with on_accept bound as handler
	m_acceptor.async_accept(*socket.get(), 
		[this, socket](const boost::system::error_code& error)
		{
			on_accept(error, socket);
		});
}

void Acceptor::on_accept(const boost::system::error_code& ec, 
	std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	if (!ec)
	{
		// Accept succeeded, start handling requests
		(new Service(socket))->start_handling();
	}
	else
	{
		// Accept failed, print error
		std::cout << "[" << std::this_thread::get_id() << "]"
			<< "[ERROR] Error code: " << ec.value() 
			<< ". Error message: " << ec.message() << "\n";
	}
	
	if (!m_is_stopped.load())
	{
		// Initialize new accept operation if not stopped
		init_accept();
	}
	else
	{
		// Stop accepting and free allocated resources
		m_acceptor.close();
	}
}

// TODO: Add ip address?
Acceptor::Acceptor(boost::asio::io_service& ios, unsigned short port_num) :
	m_ios(ios), 
	m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(
		boost::asio::ip::address_v4::any(), port_num)),
	m_is_stopped(false)
{
}

Acceptor::~Acceptor()
{
}

void Acceptor::start()
{
	m_acceptor.listen();
	init_accept();
}

void Acceptor::stop()
{
	m_is_stopped.store(true);
}

//-------------------------------------------------------------------------------

Server::Server()
{
	// Create new work
	m_work.reset(new boost::asio::io_service::work(m_ios));
}

Server::~Server()
{
}

void Server::start(unsigned short port_num, unsigned int thread_pool_size)
{
	assert(thread_pool_size > 0);
	
	// Create and start acceptor
	m_acceptor.reset(new Acceptor(m_ios, port_num));
	m_acceptor->start();

	// Create threads and add them to thread pool
	for (unsigned int i = 0; i < thread_pool_size; i++)
	{
		std::unique_ptr<std::thread> th(
			new std::thread([this]()
			{
				m_ios.run();
			}));
		m_thread_pool.push_back(std::move(th));	
	}
}

void Server::stop()
{
	// Stop acceptor and io_service
	m_acceptor->stop();
	m_ios.stop();

	// Join threads
	for (auto& th : m_thread_pool)
	{
		th->join();
	}
}

//-------------------------------------------------------------------------------

void Client::on_request_complete(std::shared_ptr<Session> session)
{
	// Shut down connection
	boost::system::error_code ignored_ec;
	session->m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
		ignored_ec);
	
	// Lock active sessions, find session and remove it
	std::unique_lock<std::mutex> lock(m_active_sessions_guard);
	auto it = m_active_sessions.find(session->m_id);
	if (it != m_active_sessions.end())
		m_active_sessions.erase(it);

	lock.unlock();

	// If no session errors and session was cancelled
	boost::system::error_code ec;
	if (!session->m_ec && session->m_was_cancelled)
		ec = boost::asio::error::operation_aborted;
	else
		ec = session->m_ec;

	// Call callback
	session->m_callback(session->m_id, session->m_response, ec);
}

Client::Client()
{
	m_work.reset(new boost::asio::io_service::work(m_ios));
	m_thread.reset(new std::thread(
		[this]()
		{
			m_ios.run();
		}));
}

Client::~Client()
{
}

void Client::emulate_long_computation_op(unsigned int duration_sec, 
	const std::string& raw_ip_address, unsigned short port_num, 
	Callback callback, unsigned int request_id)
{
	// Prepare request
	std::string request = "EMULATE_LONG_CALC_OP " 
		+ std::to_string(duration_sec) + "\n";

	// Prepare new session
	std::shared_ptr<Session> session = std::shared_ptr<Session>(new Session(
		m_ios, raw_ip_address, port_num, request, request_id,
		callback));
	session->m_socket.open(session->m_endpoint.protocol());

	// Add new session to active sessions
	std::unique_lock<std::mutex> lock(m_active_sessions_guard);
	m_active_sessions[request_id] = session;
	lock.unlock();

	// Connect to endpoint and read response
	session->m_socket.async_connect(session->m_endpoint,
		[this, session](const boost::system::error_code& ec)
		{
		// If connection error
		if (ec)
		{
			session->m_ec = ec;
			on_request_complete(session);
			return;
		}
		
		// If session cancelled
		std::unique_lock<std::mutex> cancel_lock(
			session->m_cancel_guard);
		if (session->m_was_cancelled)
		{
			on_request_complete(session);
			return;
		}
		
		// Read response
		boost::asio::async_read_until(session->m_socket,
			session->m_response_buffer, '\n',
			[this, session](const boost::system::error_code& ec,
				std::size_t bytes_transferred)
			{
			// If error
			if (ec)
			{
				session->m_ec = ec;
			}
			else
			{
				std::istream strm(
					&session->m_response_buffer);
				std::getline(strm, session->m_response);
			}
			
			on_request_complete(session);
			});
		});
}

void Client::cancel_request(unsigned int request_id)
{
	// Find request
	std::unique_lock<std::mutex> lock(m_active_sessions_guard);
	auto it = m_active_sessions.find(request_id);
	if(it != m_active_sessions.end())
	{
		// Cancel session if found
		std::unique_lock<std::mutex>
			cancel_lock(it->second->m_cancel_guard);
		it->second->m_was_cancelled = true;
		it->second->m_socket.cancel();
	}
}

void Client::close()
{
	// Destroy work object. This allows the thread to exit when there are no
	// async. operations pending.
	m_work.reset(NULL);

	// Wait for IO thread to exit
	m_thread->join();
}

}}; // Namespace zed::net

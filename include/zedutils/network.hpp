#include <boost/predef.h> // Tools to indentify the OS

// This is needed to enable cancelling of I/O operations on
// Windows XP, Windows Server 2003 and earlier.
#ifdef BOOST_OS_WINDOWS
	#define _WIN32_WINNT 0x0501
#if _WIN32_WINNT <= 0x0502 // Windows Server 2003 or earlier
	#define BOOST_ASIO_DISABLE_IOCP
	#define BOOST_ASIO_ENABLE_CANCELIO
#endif
#endif

#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>

#include <sl/Camera.hpp>

#include <atomic>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace zed { namespace net { 


//--------------------------------------------------------------------------------

/* 
Class responsible for handling a single client by reading the request message,
processing it and sending back the response message. This class represents a
single service provided by the server application.
*/
class Service
{
private:
	std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
	std::string m_response;
	boost::asio::streambuf m_request;

public:
	

private:
	// Here we check for errors during receiving and process the request
	void on_request_received(const boost::system::error_code& ec,
		std::size_t bytes);

	// Here we check for errors during sending and finish the repsonse
	void on_response_sent(const boost::system::error_code& ec,
		std::size_t bytes);

	// Here we perform the cleanup
	void on_finish();

	// Here we parse the request, process it and prepare the response
	std::string process_request(boost::asio::streambuf& request);

public:
	Service(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
	~Service();
	
	// Starts the services async. operations
	void start_handling();
	
};

//--------------------------------------------------------------------------------

class Acceptor
{
private:
	boost::asio::io_service& m_ios;
	boost::asio::ip::tcp::acceptor m_acceptor;
	std::atomic<bool> m_is_stopped;

public:

private:
	// Here we initiate a new async. accept operation
	void init_accept();

	// Here we decide what the acceptor should do after it has accepted a
	// new connection
	void on_accept(const boost::system::error_code& ec,
		std::shared_ptr<boost::asio::ip::tcp::socket> socket);

public:
	Acceptor(boost::asio::io_service& ios, unsigned short port_num);
	~Acceptor();
	
	// Here we start accepting incoming connection requests
	void start();

	// Here we stop accepting incoming connection requests
	void stop();
};

//--------------------------------------------------------------------------------

class Server
{
private:
	boost::asio::io_service m_ios;
	std::unique_ptr<boost::asio::io_service::work> m_work;
	std::unique_ptr<Acceptor> m_acceptor;
	std::vector<std::unique_ptr<std::thread>> m_thread_pool;

public:

private:
	
public:
	Server();
	~Server();

	// Starts the server
	void start(unsigned short port_num, unsigned int thread_pool_size);

	// Stops the server
	void stop();
};

//--------------------------------------------------------------------------------

// Define function pointer type that points to the callback function which is
// called when a request is complete.
typedef void(*Callback) (unsigned int request_id, const std::string& response,
	const boost::system::error_code& ec);

//--------------------------------------------------------------------------------

struct Session
{
	boost::asio::ip::tcp::socket m_socket;		// Socket for comm.
	boost::asio::ip::tcp::endpoint m_endpoint;	// Remote endpoint
	std::string m_request;				// Request string
	
	boost::asio::streambuf m_response_buffer; 	// Storing of response
	std::string m_response;				// Response rep.
	
	
	boost::system::error_code m_ec;			// Error

	unsigned int m_id;				// Unique ID
	
	Callback m_callback;				// Callback function

	bool m_was_cancelled;
	std::mutex m_cancel_guard;
	
	Session(boost::asio::io_service& ios, const std::string& raw_ip_address,
		unsigned short port_num, const std::string& request, 
		unsigned int id, Callback callback) :
		m_socket(ios), 
		m_endpoint(boost::asio::ip::address::from_string(
			raw_ip_address), port_num), 
		m_request(request), 
		m_id(id),
		m_callback(callback), 
		m_was_cancelled(false) {}
};

//--------------------------------------------------------------------------------

class Client : public boost::noncopyable
{
private:
	boost::asio::io_service m_ios;
	std::map<int, std::shared_ptr<Session>> m_active_sessions;
	std::mutex m_active_sessions_guard;
	std::unique_ptr<boost::asio::io_service::work> m_work;
	std::unique_ptr<std::thread> m_thread;

public:

private:
	// Shuts down the connection. May fail if socket is not connected.
	void on_request_complete(std::shared_ptr<Session> session);

public:
	Client();
	~Client();

	void emulate_long_computation_op(unsigned int duration_sec, 
		const std::string& raw_ip_address, unsigned short port_num,
		Callback callback, unsigned int request_id);
	
	void cancel_request(unsigned int request_id);
	
	void close();
};

}}; // Namespace zed::net

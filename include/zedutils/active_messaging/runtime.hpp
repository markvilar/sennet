#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <atomic>
#include <memory>
#include <thread>

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/ref.hpp>

#include <zedutils/active_messaging/action.hpp>
#include <zedutils/active_messaging/connection.hpp>
#include <zedutils/active_messaging/container_device.hpp>

namespace zed { namespace am {

class connection; // Forward declaration.

// Boost documentation references:
// https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/reference.html
// https://www.boost.org/doc/libs/1_67_0/libs/assert/doc/html/assert.html

class runtime
{
private:
	// IO service.
	boost::asio::io_service m_io_service;

	// Connection acceptor.
	boost::asio::ip::tcp::acceptor m_acceptor;

	// Map with endpoints and connections.
	std::map<boost::asio::ip::tcp::endpoint, std::shared_ptr<connection>>
		m_connections;

	// Execution thread.
	std::thread m_exec_thread;

	// Parcel queue.
	boost::lockfree::queue<std::vector<char>*> m_parcel_queue;

	// Action queue.
	boost::lockfree::queue<std::function<void(runtime&)>*> m_local_queue;

	// Stop flag.
	std::atomic<bool> m_stop_flag;

	// Main function handler for bootstrapping.
	std::function<void(runtime&)> m_main;

	// The number of clients to wait for before executing the main function.
	boost::uint64_t m_wait_for;

public:
	runtime(
		std::string port,
		std::function<void(runtime&)> f,
		boost::uint64_t wait_for
		);
		
	~runtime() 
	{ 
		stop(); 
	}
	
	boost::asio::io_service& get_io_service() 
	{ 
		return m_io_service; 
	}

	boost::lockfree::queue<std::vector<char>*>& get_parcel_queue() 
	{ 
		return m_parcel_queue;
	}

	boost::lockfree::queue<std::function<void(runtime&)>*>&
		get_local_queue()
	{
		return m_local_queue;
	}

	std::map<boost::asio::ip::tcp::endpoint, std::shared_ptr<connection>>&
		get_connections()
	{
		return m_connections;
	}

	// Launch the execution thread and the start accepting connections.
	void start();

	// Stop the I/O service and execution thread.
	void stop();

	// Accepts connections and parcels until stop() is called.
	void run();

	// Connect to another node.
	std::shared_ptr<connection> connect(
		std::string host,
		std::string port
		);

	// Asynchronously accept a new connection.
	void async_accept();

	// Handler for new connections.
	void handle_accept(
		boost::system::error_code const& error,
		std::shared_ptr<connection> conn
		);

private:
	friend class connection;

	// Execute actions until stop() is called.
	void exec_loop();

	// Serializes an action object into a parcel.
	std::vector<char>* serialize_parcel(action const& act);

	// Deserializes a parcel into an action object.
	action* deserialize_parcel(std::vector<char>& raw_msg);
}; // class runtime

} // namespace am
}; // namespace zed

#endif // RUNTIME_HPP

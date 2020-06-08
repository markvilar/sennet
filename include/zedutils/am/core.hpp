// Boost documentation references:
// https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/reference.html
// https://www.boost.org/doc/libs/1_67_0/libs/assert/doc/html/assert.html
#pragma once

#include <atomic>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/ref.hpp>

#include <sl/Camera.hpp>

namespace am {

// Forward declaration.
class runtime;
class zed_runtime;

namespace action {

class base_action 
{
private:

public:
	virtual ~base_action() {}
	
	virtual void operator()(runtime& rt) = 0;
	virtual void operator()(zed_runtime& rt) = 0;

	virtual base_action* clone() const = 0;

	// Member function needed in order to use Boost.Serialization.
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {};
};

} // namespace action


class connection : public std::enable_shared_from_this<connection>
{
private:
	// Reference to the Runtime object.
	runtime& m_runtime;

	// IP/TCP socket of the connection.
	boost::asio::ip::tcp::socket m_socket;

	// Size of the incoming parcel.
	boost::uint64_t m_in_size;

	// Buffer for incoming parcel.
	std::vector<char>* m_in_buffer;

public:
	connection(runtime& rt);
		
	~connection();

	// Returns the reference of the connection socket.
	boost::asio::ip::tcp::socket& get_socket() { return m_socket; }

	// Returns the remote endpoint of the connection socket.
	boost::asio::ip::tcp::endpoint get_remote_endpoint() const;

	// Retruns the local endpoint of the connection socket.
	boost::asio::ip::tcp::endpoint get_local_endpoint() const;

	// Asynchronously read a parcel from the socket.
	void async_read();

	// Asynchronously write an action to the socket.
	void async_write(action::base_action const& act);

	// Asynchronously write an action to the socket.
	void async_write(
		action::base_action const& act,
		std::function<void(boost::system::error_code const&)> handler
		);

	// Asynchronously write worker. It performs the action serializing.
	void async_write_worker(
		std::shared_ptr<action::base_action> act,
		std::function<void(boost::system::error_code const&)> handler
		);

	// Handler for parcel size.
	void handle_read_size(boost::system::error_code const& error);

	// Handler for data.
	void handle_read_data(boost::system::error_code const& error);

	// Handler for write.
	void handle_write(
		boost::system::error_code const& error,
		std::shared_ptr<boost::uint64_t> out_size,
		std::shared_ptr<std::vector<char>> out_buffer,
		std::function<void(boost::system::error_code const&)> handler
		);
};


class runtime
{
private:
	// IO service.
	boost::asio::io_service m_io_service;

	// Execution thread.
	std::thread m_exec_thread;

	// Connection acceptor.
	boost::asio::ip::tcp::acceptor m_acceptor;

	// Map with endpoints and connections.
	std::map<boost::asio::ip::tcp::endpoint, std::shared_ptr<connection>>
		m_connections;

	// Main function handler for bootstrapping.
	std::function<void(runtime&)> m_main;

	// The number of clients to wait for before executing the main function.
	boost::uint64_t m_wait_for;

protected:
	// Stop flag.
	std::atomic<bool> m_stop_flag;

	// Action queue.
	boost::lockfree::queue<std::function<void(runtime&)>*> m_local_queue;

	// Parcel queue.
	boost::lockfree::queue<std::vector<char>*> m_parcel_queue;

public:
	// Constructor.
	runtime(
		std::string port,
		std::function<void(runtime&)> f 
			= std::function<void(runtime&)>(),
		boost::uint64_t wait_for = 1
		);
			
	// Destructor.
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

	// Finds connection based on address.
	std::shared_ptr<connection> find_connection(
		const std::string& addr
		);

	// Finds connection based on address and port.
	std::shared_ptr<connection> find_connection(
		const std::string& addr,
		const unsigned short port
		);

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
	virtual void exec_loop();

protected:
	// Serializes an action object into a parcel.
	std::vector<char>* serialize_parcel(action::base_action const& act);

	// Deserializes a parcel into an action object.
	action::base_action* deserialize_parcel(std::vector<char>& raw_msg);

};


class zed_runtime : public runtime
{
private:
	// ZED camera.
	sl::Camera m_zed;

	// Main function handler for bootstrapping.
	std::function<void(zed_runtime&)> m_main;

	// Path to root directory for data storage.
	std::string m_root;

public:
	zed_runtime(
		std::string port, 
		std::string root,
		std::function<void(runtime&)> f 
			= std::function<void(runtime&)>(),
		boost::uint64_t wait_for = 1
		);

	~zed_runtime();

	// Opens the ZED camera.
	sl::ERROR_CODE open_zed(sl::InitParameters& init_params);

	// Closes the ZED camera.
	void close_zed();

	// Checks whether the ZED is opened or not.
	bool is_zed_opened();

	// Checks whether the ZED is recording or not.
	bool is_zed_recording();

	// Gets ZED recording status.
	sl::RecordingStatus zed_recording_status();

	// Gets ZED recording parameters.
	sl::RecordingParameters zed_recording_parameters();

	// Enables recording for the ZED.
	sl::ERROR_CODE enable_zed_recording(sl::RecordingParameters rec_params);

	// Disables recording for the ZED.
	void disable_zed_recording();

	// Retrieves image from the ZED.
	sl::ERROR_CODE retrieve_zed_image(
		sl::Mat& m, 
		sl::VIEW view = sl::VIEW::LEFT, 
		sl::MEM mem = sl::MEM::CPU,
		sl::Resolution res = sl::Resolution(0, 0)
		);

	// Gets timestamp from the ZED.
	sl::Timestamp get_zed_timestamp(sl::TIME_REFERENCE& ref);

private:
	// Deserializes parcels and executes actions.
	void exec_loop();
};

}; // namespace am

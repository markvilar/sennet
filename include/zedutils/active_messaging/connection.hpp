#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/bind.hpp>
//#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/lockfree/queue.hpp>
//#include <boost/ref.hpp>

#include <zedutils/active_messaging/action.hpp>
#include <zedutils/active_messaging/runtime.hpp>

namespace zed { namespace am {

class runtime; // Forward declaration.

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

	// Asynchronously read a parcel from the socket.
	void async_read();

	// Asynchronously write an action to the socket.
	void async_write(action const& act);

	// Asynchronously write an action to the socket.
	void async_write(
		action const& act,
		std::function<void(boost::system::error_code const&)> handler
		);

	// Asynchronously write worker. It performs the action serializing.
	void async_write_worker(
		std::shared_ptr<action> act,
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
}; // class connection
} // namespace am
}; // namespace zed

#endif // CONNECTION_HPP

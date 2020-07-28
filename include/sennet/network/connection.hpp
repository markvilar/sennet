#pragma once
#include <sennet/snpch.hpp>

#include <sennet/core/base.hpp>
#include <sennet/messages/message.hpp>

#include <boost/asio.hpp>

// TODO: Implement sennet::endpoint and sennet::socket!

namespace sennet
{

class connection : public std::enable_shared_from_this<connection>
{
	typedef std::function<void(boost::system::error_code const&)> 
		write_callback_fn;

public:
	connection(boost::asio::io_service& service);
	virtual ~connection();

	boost::asio::ip::tcp::socket& get_socket();
	boost::asio::ip::tcp::endpoint get_remote_endpoint() const;
	boost::asio::ip::tcp::endpoint get_local_endpoint() const;

	void async_read();
	void async_write(const message& msg);
	void async_write(const message& msg, write_callback_fn handler);
	void async_write_worker(const message& msg, write_callback_fn handler);

private:
	void handle_read_size(boost::system::error_code const& error);
	void handle_read_data(boost::system::error_code const& error);
	void handle_write(boost::system::error_code const& error,
		std::shared_ptr<boost::uint64_t> out_size,
		std::shared_ptr<std::vector<char>> out_buffer,
		std::function<void(boost::system::error_code const&)> handler);


private:
	boost::asio::ip::tcp::socket m_socket;
	boost::uint64_t m_in_size;
	std::vector<char>* m_in_buffer;
};

}

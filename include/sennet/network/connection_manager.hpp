#pragma once
#include <sennet/snpch.hpp>

#include <sennet/core/base.hpp>

#include <boost/asio.hpp>

#include <sennet/messages/message.hpp>

#include <sennet/network/connection.hpp>
#include <sennet/network/message_encoder.hpp>

#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>

// Boost documentation references:
// https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/reference.html
// https://www.boost.org/doc/libs/1_67_0/libs/assert/doc/html/assert.html

namespace sennet 
{

class connection_manager
{

public:
	using msg_callback_fn = std::function<void(message&)>;

	connection_manager(std::string port, uint64_t wait_for = 1);
	~connection_manager();
	
	boost::asio::io_service& get_io_service();

	std::queue<std::vector<char>*>& get_inbound_queue();
	std::queue<std::pair<ref<connection>, ref<message>>>& get_outbound_queue();
		
	std::map<boost::asio::ip::tcp::endpoint, ref<connection>>& get_connections();
	ref<connection> find_connection(const std::string& addr, 
		const unsigned short port);

	void set_message_callback(const msg_callback_fn& callback);
		
	void start();
	void stop();
	void run();

	ref<connection> connect(std::string host, std::string port);

	void async_accept();
	void on_accept(const boost::system::error_code& error, 
		ref<connection> conn);

private:
	friend class connection;
	
	void exec_loop();

private:
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::acceptor m_acceptor;

	std::queue<std::pair<ref<connection>, ref<message>>> m_outbound_queue;
	std::queue<std::vector<char>*> m_inbound_queue;
	std::map<boost::asio::ip::tcp::endpoint, ref<connection>> m_connections;

	std::atomic<bool> m_stop_flag;
	std::thread m_exec_thread;
	std::mutex m_mutex;

	uint64_t m_wait_for;
	
	msg_callback_fn m_message_callback;
};

}

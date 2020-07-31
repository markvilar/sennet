#pragma once
#include <sennet/snpch.hpp>

#include <boost/asio.hpp>

#include <sennet/core/base.hpp>
#include <sennet/messages/message.hpp>
#include <sennet/network/connection.hpp>

namespace sennet 
{

class connection_manager
{
	typedef std::vector<char> parcel;

public:
	using msg_callback_fn = std::function<void(message&)>;

	connection_manager(std::string port, uint64_t wait_for = 1);
	~connection_manager();
	
	boost::asio::io_service& get_io_service();

	std::queue<parcel*>& get_inbound_queue();
	std::queue<std::pair<ref<connection>, ref<message>>>& get_outbound_queue();
	std::map<boost::asio::ip::tcp::endpoint, ref<connection>>& get_connections();
	
	void set_message_callback(const msg_callback_fn& callback);
		
	void start();
	void stop();
	void run();

	ref<connection> connect(std::string host, std::string port);
	ref<connection> connection_search(const std::string& addr, 
		const unsigned short port);
	void push_message(ref<connection> conn, const message& msg);

	void async_accept();
	void on_accept(const boost::system::error_code& error, 
		ref<connection> conn);

private:
	void exec_loop();

private:
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::acceptor m_acceptor;

	std::queue<std::pair<ref<connection>, ref<message>>> m_outbound_queue;
	std::queue<parcel*> m_inbound_queue;
	std::map<boost::asio::ip::tcp::endpoint, ref<connection>> m_connections;

	std::atomic<bool> m_stop_flag;
	std::thread m_exec_thread;
	std::mutex m_mutex;

	uint64_t m_wait_for;
	
	msg_callback_fn m_message_callback;
};

}

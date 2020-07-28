#pragma once
#include <sennet/snpch.hpp>

#include <sennet/core/base.hpp>

#include <sennet/network/connection.hpp>

#include <sennet/messages/message.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/ref.hpp>

// Boost documentation references:
// https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/reference.html
// https://www.boost.org/doc/libs/1_67_0/libs/assert/doc/html/assert.html

namespace sennet 
{

class connection_manager
{

public:
	connection_manager(std::string port,
		boost::uint64_t wait_for = 1);
	~connection_manager();
	
	boost::asio::io_service& get_io_service();
	boost::lockfree::queue<std::vector<char>*>& get_inbound_queue();
	boost::lockfree::queue<message*>& get_outbound_queue();

	std::map<boost::asio::ip::tcp::endpoint, ref<connection>>& get_connections();

	ref<connection> find_connection(const std::string& addr, 
		const unsigned short port);
		
	void start();
	void stop();
	void run();

	ref<connection> connect(std::string host, std::string port);
	void async_accept();
	void handle_accept(const boost::system::error_code& error,
		ref<connection> conn);

protected:
	std::vector<char>* serialize_parcel(const message& msg);
	message* deserialize_parcel(std::vector<char>& raw_msg);

private:
	friend class connection;
	
	virtual void exec_loop();

protected:
	std::atomic<bool> m_stop_flag;
	boost::lockfree::queue<message*> m_outbound_queue;
	boost::lockfree::queue<std::vector<char>*> m_inbound_queue;

private:
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::acceptor m_acceptor;
	std::map<boost::asio::ip::tcp::endpoint, ref<connection>> m_connections;
	std::function<void(connection_manager&)> m_main;
	boost::uint64_t m_wait_for;
	std::thread m_exec_thread;

};

}

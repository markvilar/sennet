#pragma once
#include <sennet/snpch.hpp>

#include <boost/asio.hpp>

#include <sennet/core/base.hpp>
#include <sennet/messages/message.hpp>

namespace sennet
{

class connection : public std::enable_shared_from_this<connection>
{
	// Asynchronous connection class. 
	typedef std::function<void(ref<message_encoding>)> parcel_callback_fn;

public:
	connection(boost::asio::io_service& service);
	virtual ~connection();

	boost::asio::ip::tcp::socket& get_socket();
	boost::asio::ip::tcp::endpoint get_remote_endpoint() const;
	boost::asio::ip::tcp::endpoint get_local_endpoint() const;

	void set_data_callback(const parcel_callback_fn& callback);

	void async_read();
	void async_write(ref<message_encoding> out_buffer);

private:
	void on_read_size(const boost::system::error_code& error);
	void on_read_data(const boost::system::error_code& error);
	void on_write(const boost::system::error_code& error,
		ref<uint64_t> out_size,
		ref<message_encoding> out_buffer);

private:
	boost::asio::ip::tcp::socket m_socket;
	uint64_t m_in_size;
	ref<message_encoding> m_in_buffer;

	parcel_callback_fn m_data_callback;
};

}

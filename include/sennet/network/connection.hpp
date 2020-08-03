#pragma once
#include <sennet/snpch.hpp>

#include <boost/asio.hpp>

#include <sennet/core/base.hpp>

namespace sennet
{

class connection : public std::enable_shared_from_this<connection>
{
	// Asynchronous connection class. 

	typedef std::vector<char> parcel;
	typedef std::function<void(std::vector<char>*)> parcel_callback_fn;

public:
	connection(boost::asio::io_service& service);
	virtual ~connection();

	boost::asio::ip::tcp::socket& get_socket();
	boost::asio::ip::tcp::endpoint get_remote_endpoint() const;
	boost::asio::ip::tcp::endpoint get_local_endpoint() const;

	void set_data_callback(const parcel_callback_fn& callback);

	void async_read();
	void async_write(std::shared_ptr<parcel> out_buffer);

private:
	void on_read_size(const boost::system::error_code& error);
	void on_read_data(const boost::system::error_code& error);
	void on_write(const boost::system::error_code& error,
		std::shared_ptr<uint64_t> out_size,
		std::shared_ptr<parcel> out_buffer);

private:
	boost::asio::ip::tcp::socket m_socket;
	uint64_t m_in_size;
	parcel* m_in_buffer;

	parcel_callback_fn m_data_callback;
};

}

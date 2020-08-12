#pragma once
#include <Sennet/pch.hpp>

#include <boost/asio.hpp>

#include <Sennet/Core/Base.hpp>
#include <Sennet/Messages/Message.hpp>

namespace Sennet
{

class Connection : public std::enable_shared_from_this<Connection>
{
	// Asynchronous Connection class. 
	typedef std::function<void(Ref<MessageEncoding>)> DataCallbackFn;

public:
	Connection(boost::asio::io_service& service);
	virtual ~Connection();

	boost::asio::ip::tcp::socket& GetSocket();

	boost::asio::ip::tcp::endpoint GetRemoteEndpoint() const;
	boost::asio::ip::tcp::endpoint GetLocalEndpoint() const;
	std::pair<std::string, unsigned short> GetRemoteInformation() const;
	std::pair<std::string, unsigned short> GetLocalInformation() const;

	void SetDataCallback(const DataCallbackFn& callback);

	void AsyncRead();
	void AsyncWrite(Ref<MessageEncoding> outBuffer);

private:
	void OnReadSize(const boost::system::error_code& error);
	void OnReadData(const boost::system::error_code& error);
	void OnWrite(const boost::system::error_code& error,
		Ref<uint64_t> outSize,
		Ref<MessageEncoding> outBuffer);

private:
	boost::asio::ip::tcp::socket m_Socket;
	uint64_t m_InSize;
	Ref<MessageEncoding> m_InBuffer;

	DataCallbackFn m_DataCallback;
};

}

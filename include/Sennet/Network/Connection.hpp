#pragma once

#include <asio.hpp>

#include <Sennet/Core/Base.hpp>
#include <Sennet/Messages/Message.hpp>

namespace Sennet
{

class Connection : public std::enable_shared_from_this<Connection>
{
	// Asynchronous Connection class. 
	typedef std::function<void(Ref<MessageEncoding>)> DataCallbackFn;

public:
	Connection(asio::io_service& service);
	virtual ~Connection();

	asio::ip::tcp::socket& GetSocket();

	asio::ip::tcp::endpoint GetRemoteEndpoint() const;
	asio::ip::tcp::endpoint GetLocalEndpoint() const;
	std::pair<std::string, unsigned short> GetRemoteInformation() const;
	std::pair<std::string, unsigned short> GetLocalInformation() const;

	void SetDataCallback(const DataCallbackFn& callback);

	void AsyncRead();
	void AsyncWrite(Ref<MessageEncoding> outBuffer);

private:
	void OnReadSize(const asio::error_code& error);
	void OnReadData(const asio::error_code& error);
	void OnWrite(const asio::error_code& error, Ref<uint64_t> outSize,
		Ref<MessageEncoding> outBuffer);

private:
	asio::ip::tcp::socket m_Socket;
	uint64_t m_InSize;
	Ref<MessageEncoding> m_InBuffer;

	DataCallbackFn m_DataCallback;
};

}

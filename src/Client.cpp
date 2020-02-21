#include <ZEDutils/Client.hpp>

Client::Client(boost::asio::io_service& svc, const std::string& host, 
	const std::string& port)
	: io_service(svc), socket(io_service)
{
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(
		boost::asio::ip::tcp::resolver::query(host, port));
	boost::asio::connect(this->socket, endpoint);
}
		
void Client::send(const std::string& message)
{
	socket.send(boost::asio::buffer(message));
}

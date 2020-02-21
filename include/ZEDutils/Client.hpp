#include <boost/asio.hpp>

#include <string>

class Client
{
private:
	boost::asio::io_service& io_service;
	boost::asio::ip::tcp::socket socket;
public:
	Client(boost::asio::io_service& svc, const std::string& host,
		const std::string& port);
	void send(const std::string& message);
};

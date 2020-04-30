#include <ZEDutils/types.hpp>

#include <boost/asio.hpp>

#include <sl/Camera.hpp>

#include <iostream>
#include <memory>
#include <thread>
#include <vector>

int main(int argc, char* argv[])
{
	// Step 1: Assume that the client application has already obtained the
	// IP address and protocol port number of the target server.
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	
	try
	{
		// Step 2: Creating an endpoint designating a target server
		// application.
		boost::asio::ip::tcp::endpoint 
			ep(boost::asio::ip::address::from_string(raw_ip_address),
			port_num);

		boost::asio::io_service ios;

		// Step 3: Creating and opening a socket.
		boost::asio::ip::tcp::socket sock(ios, ep.protocol());

		// Step 4: Connecting a socket.
		sock.connect(ep);

		// At this point socket 'sock' is connected to the server
		// application and can be used to send data to or receive data
		// from it.
	}
	catch (boost::system::system_error& e)
	{
		std::cout << "Error occured! Error code: " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}
	
	return 0;
}

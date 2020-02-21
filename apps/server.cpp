#include <ZEDutils/Client.hpp>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <iostream>


static const int PORT = 52275;


void client_thread()
{
	boost::asio::io_service svc;
	Client client(svc, "127.0.0.1", std::to_string(PORT));
	
	client.send("Hello world!\n");
	client.send("Bye world!\n");
}


void server_thread()
{
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::endpoint endpoint(
			boost::asio::ip::tcp::v4(), PORT);
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

		boost::asio::ip::tcp::socket socket(io_service);
		acceptor.accept(socket);
		
		boost::asio::streambuf sb;
		boost::system::error_code ec;
		while (boost::asio::read(socket, sb, ec))
		{
			std::cout << "Received: '" << &sb << "'\n";
			
			if (ec)
			{
				std::cout << "Status: " << ec.message() << "\n";
				break;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}


int main()
{
	boost::thread_group tg;
	tg.create_thread(server_thread);

	boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	tg.create_thread(client_thread);
	
	tg.join_all();
	return 0;
}

#include <functional>

#include <sennet/sennet.hpp>
#include <sennet/messages/message.hpp>

void handle_message(sennet::message& msg)
{
	std::cout << "Server got message: " << msg.to_string() << "\n";
}

int main()
{
	sennet::log::init();
	sennet::connection_manager manager("7000", 1);
	manager.set_message_callback(std::bind(handle_message, 
		std::placeholders::_1));
	manager.start();
	manager.run();
	SN_INFO("Server finished.");
	return 0;
}

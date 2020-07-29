#include <sennet/sennet.hpp>
#include <sennet/messages/message.hpp>

int main()
{
	sennet::log::init();
	sennet::connection_manager manager("6000", 1);
	SN_INFO("Client attempting to connect.");
	manager.connect("localhost", "7000");
	manager.start();
	manager.run();
	SN_INFO("Client finished.");
	return 0;
}

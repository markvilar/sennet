#include <functional>
#include <thread>

#include <Sennet/Sennet.hpp>

// Register messages.
namespace
{

zpp::serializer::register_types<
	zpp::serializer::make_type<Sennet::HelloMessage,
	zpp::serializer::make_id("Sennet::HelloMessage")>,
	zpp::serializer::make_type<Sennet::ImageMessage,
	zpp::serializer::make_id("Sennet::ImageMessage")>
> _;

}

void IOWorker(Sennet::ConnectionManager& manager)
{
	manager.Run();
}

int main()
{
	Sennet::Log::Init();
	Sennet::ConnectionManager manager("6000", 1);
	SN_INFO("Client attempting to connect.");
	auto connection = manager.Connect("localhost", "7000");
	manager.Start();

	std::thread IOThread(IOWorker, std::ref(manager));
	SN_INFO("Client: Started IO thread.");

	SN_INFO("Client: Sending messages.");
	Sennet::HelloMessage helloMsg("hello world!");
	auto vec = std::vector<unsigned char>(1920*1080*3, 150);

	Sennet::ImageMessage imageMsg(vec, 1920, 1080, 3);
	
	manager.PushMessage(connection, helloMsg);
	manager.PushMessage(connection, imageMsg);

	if (IOThread.joinable())
	{
		IOThread.join();
	}

	SN_INFO("Client: Finished.");
	return 0;
}

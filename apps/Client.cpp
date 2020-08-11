#include <chrono>
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

int main()
{
	Sennet::Log::Init();
	Sennet::ConnectionManager manager(6000, 1);
	SN_INFO("Client attempting to connect.");
	auto connection = manager.Connect("localhost", "7000");
	manager.Start();
	
	auto helloMsg = Sennet::CreateRef<Sennet::HelloMessage>("hello world!");
	auto imageMsg = Sennet::CreateRef<Sennet::ImageMessage>(
		std::vector<unsigned char>(1920*1080*3, 150), 1920, 1080, 3);
	
	SN_INFO("Pushing messages.");
	manager.PushMessage(connection, helloMsg);
	manager.PushMessage(connection, imageMsg);

	for (int i = 0; i < 20; i++)
	{
		SN_INFO("Running...");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	SN_INFO("Client: Finished.");
	return 0;
}

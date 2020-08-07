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

void HandleMessage(Sennet::Ref<Sennet::Message>& msg)
{
	SN_TRACE("Server: {0}", msg->ToString());
}

void IOWorker(Sennet::ConnectionManager& manager)
{
	manager.Run();
}

int main()
{
	Sennet::Log::Init();
	Sennet::ConnectionManager manager("7000", 1);
	manager.SetMessageCallback(std::bind(HandleMessage, 
		std::placeholders::_1));
	manager.Start();

	std::thread IOThread(IOWorker, std::ref(manager));
	SN_TRACE("Server: Started IO thread.");

	if (IOThread.joinable())
	{
		IOThread.join();
	}

	SN_INFO("Server: Finished.");
	return 0;
}

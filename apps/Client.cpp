#include <chrono>
#include <functional>
#include <thread>

#include <Sennet/Sennet.hpp>

// Register messages.
namespace
{

zpp::serializer::register_types<
	zpp::serializer::make_type<Sennet::TextMessage,
	zpp::serializer::make_id("Sennet::TextMessage")>,
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
	
	auto textMsg = Sennet::CreateRef<Sennet::TextMessage>(
		connection->GetLocalInformation().first,
		connection->GetLocalInformation().second,
		"hello world!");

	auto imageMsg = Sennet::CreateRef<Sennet::ImageMessage>(
		connection->GetLocalInformation().first,
		connection->GetLocalInformation().second,
		Sennet::Image(std::vector<unsigned char>(1920*1080*3, 150),
		1920, 1080, 3));

	SN_INFO("Submitting messages.");
	manager.SubmitMessage(connection, textMsg);
	manager.SubmitMessage(connection, imageMsg);

	for (int i = 0; i < 20; i++)
	{
		auto localEndpoints = manager.GetLocalEndpointsData();
		auto remoteEndpoints = manager.GetRemoteEndpointsData();

		SN_TRACE("Local endpoints: ");
		for (auto endpoint : *localEndpoints)
		{
			SN_TRACE("{0}:{1}", endpoint.first, endpoint.second);
		}

		SN_TRACE("Remote endpoints: ");
		for (auto endpoint : *remoteEndpoints)
		{
			SN_TRACE("{0}:{1}", endpoint.first, endpoint.second);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	SN_INFO("Client: Finished.");
	return 0;
}

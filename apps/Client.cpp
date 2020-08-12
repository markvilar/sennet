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
	zpp::serializer::make_id("Sennet::ImageMessage")>,
	zpp::serializer::make_type<Sennet::ZEDCommandRequest,
	zpp::serializer::make_id("Sennet::ZEDCommandRequest")>,
	zpp::serializer::make_type<Sennet::ZEDSettingsRequest,
	zpp::serializer::make_id("Sennet::ZEDSettingsRequest")>,
	zpp::serializer::make_type<Sennet::ZEDStateRequest,
	zpp::serializer::make_id("Sennet::ZEDStateRequest")>,
	zpp::serializer::make_type<Sennet::ZEDCommandResponse,
	zpp::serializer::make_id("Sennet::ZEDCommandResponse")>,
	zpp::serializer::make_type<Sennet::ZEDSettingsResponse,
	zpp::serializer::make_id("Sennet::ZEDSettingsResponse")>,
	zpp::serializer::make_type<Sennet::ZEDStateResponse,
	zpp::serializer::make_id("Sennet::ZEDStateResponse")>
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

	auto commandRequest = Sennet::CreateRef<Sennet::ZEDCommandRequest>(
		connection->GetLocalInformation().first,
		connection->GetLocalInformation().second,
		Sennet::ZEDCommand::Shutdown);

	auto settingsRequest = Sennet::CreateRef<Sennet::ZEDSettingsRequest>(
		connection->GetLocalInformation().first,
		connection->GetLocalInformation().second,
		Sennet::ZED::InitParameters(),
		Sennet::ZED::RecordingParameters(),
		Sennet::ZED::RuntimeParameters());

	auto stateRequest = Sennet::CreateRef<Sennet::ZEDStateRequest>(
		connection->GetLocalInformation().first,
		connection->GetLocalInformation().second);
	
	SN_INFO("Pushing messages.");
	manager.PushMessage(connection, textMsg);
	manager.PushMessage(connection, imageMsg);

	// Sleep a bit in order to avoid bad alloc exception on server end.
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	manager.PushMessage(connection, commandRequest);
	manager.PushMessage(connection, settingsRequest);
	manager.PushMessage(connection, stateRequest);

	for (int i = 0; i < 20; i++)
	{
		SN_INFO("Running...");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	SN_INFO("Client: Finished.");
	return 0;
}

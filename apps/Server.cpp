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

bool OnTextMessage(Sennet::Ref<Sennet::TextMessage> msg)
{
	SN_TRACE("Server: Dispatched to OnTextMessage!");
	SN_TRACE("[{0}]: {1}:{2}, Message: {3}", 
		std::this_thread::get_id(),
		msg->GetSender().first,
		msg->GetSender().second, 
		msg->ToString());
	return false;
}

bool OnImageMessage(Sennet::Ref<Sennet::ImageMessage> msg)
{
	SN_TRACE("Server: Dispatched to OnImageMessage!");
	SN_TRACE("[{0}]: {1}:{2}, Message: {3}", 
		std::this_thread::get_id(),
		msg->GetSender().first, 
		msg->GetSender().second, 
		msg->ToString());
	return false;
}

bool OnZEDCommandRequest(Sennet::Ref<Sennet::ZEDCommandRequest> msg)
{
	SN_TRACE("Server: Dispatched to OnZEDCommandRequest!");
	SN_TRACE("[{0}]: {1}:{2}, Message: {3}", 
		std::this_thread::get_id(),
		msg->GetSender().first, 
		msg->GetSender().second, 
		msg->ToString());
	return false;
}

bool OnZEDSettingsRequest(Sennet::Ref<Sennet::ZEDSettingsRequest> msg)
{
	SN_TRACE("Server: Dispatched to OnZEDSettingsRequest!");
	SN_TRACE("[{0}]: {1}:{2}, Message: {3}", 
		std::this_thread::get_id(),
		msg->GetSender().first, 
		msg->GetSender().second, 
		msg->ToString());
	return false;
}

bool OnZEDStateRequest(Sennet::Ref<Sennet::ZEDStateRequest> msg)
{
	SN_TRACE("Server: Dispatched to OnZEDStateRequest!");
	SN_TRACE("[{0}]: {1}:{2}, Message: {3}", 
		std::this_thread::get_id(),
		msg->GetSender().first, 
		msg->GetSender().second, 
		msg->ToString());
	return false;
}

void OnMessage(Sennet::Ref<Sennet::Message> msg)
{
	SN_TRACE("Server: {0}", msg->ToString());
	Sennet::MessageDispatcher dispatcher(msg);
	dispatcher.Dispatch<Sennet::TextMessage>(
		std::bind(OnTextMessage, std::placeholders::_1));
	dispatcher.Dispatch<Sennet::ImageMessage>(
		std::bind(OnImageMessage, std::placeholders::_1));
	dispatcher.Dispatch<Sennet::ZEDCommandRequest>(
		std::bind(OnZEDCommandRequest, std::placeholders::_1));
	dispatcher.Dispatch<Sennet::ZEDSettingsRequest>(
		std::bind(OnZEDSettingsRequest, std::placeholders::_1));
	dispatcher.Dispatch<Sennet::ZEDStateRequest>(
		std::bind(OnZEDStateRequest, std::placeholders::_1));
}

int main()
{
	Sennet::Log::Init();
	Sennet::ConnectionManager manager(7000, 1);
	manager.SetMessageCallback(std::bind(OnMessage, 
		std::placeholders::_1));
	manager.Start();

	for (int i = 0; i < 20; i++)
	{
		SN_INFO("Running...");
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	SN_INFO("Server: Finished.");
	return 0;
}

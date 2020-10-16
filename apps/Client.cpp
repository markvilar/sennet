#include <chrono>
#include <functional>
#include <thread>

#include "Sennet/Sennet.hpp"

namespace
{

zpp::serializer::register_types<
	zpp::serializer::make_type<Sennet::TextMessage,
	zpp::serializer::make_id("Sennet::TextMessage")>
> _;

}

int main()
{
	Sennet::Log::Init();
	Sennet::Client client;
	bool status = client.Connect("127.0.0.1", 6000);

	bool messageSent = false;
	while (true)
	{
		if (client.IsConnected() && !messageSent)
		{
			client.Send(Sennet::CreateRef<Sennet::TextMessage>(
				"", 0, "Hello"));
			messageSent = true;
			SN_INFO("Sent message!");
		}
	}

	return 0;
}

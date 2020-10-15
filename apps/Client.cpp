#include <chrono>
#include <functional>
#include <thread>

#include <Sennet/Sennet.hpp>

int main()
{
	Sennet::Log::Init();
	Sennet::Client client;
	bool status = client.Connect("127.0.0.1", 6000);

	while (true)
	{
		if (client.IsConnected())
		{
			client.Send(Sennet::CreateRef<Sennet::TextMessage>());
			SN_INFO("Sent message!");
		}
	}

	return 0;
}

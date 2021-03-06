#include <chrono>
#include <functional>
#include <thread>

#include "Sennet/Sennet.hpp"

enum class CustomMessageTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};

class CustomClient : public Sennet::Client<CustomMessageTypes>
{
public:
	void PingServer()
	{
		Sennet::Message<CustomMessageTypes> message;
		message.Header.ID = CustomMessageTypes::ServerPing;
		std::chrono::system_clock::time_point time = 
			std::chrono::system_clock::now();

		message << time;
		SN_INFO("Message size: {0}", message.Size());
		SN_INFO("Message body size: {0}", message.Body.size());
		Send(message);
	}
};

int main(int argc, char** argv)
{
	Sennet::Log::Init();

	CustomClient client;
	client.Connect("10.42.0.35", 60000);

	bool quit = false;
	bool sent = false;
	while (!quit)
	{
		if (client.IsConnected())
		{
			if (!sent)
			{
				std::this_thread::sleep_for(
					std::chrono::seconds(1));
				SN_INFO("Pinging server!");
				client.PingServer();
				sent = true;
			}
			if (!client.Incoming().empty())
			{
				auto message = client.Incoming().pop_front().Msg;

				switch (message.Header.ID)
				{
				case CustomMessageTypes::ServerPing:
					std::chrono::system_clock::time_point t =
						std::chrono::system_clock::now();
					std::chrono::system_clock::time_point z;
					message >> z;
					auto time = std::chrono::duration<double>
						(t - z).count();
					SN_INFO("Ping: {0}", time);
					break;
				}
			}
		}
		else
		{
			SN_INFO("Server Down.");
			quit = true;
		}
	}

	return 0;
}

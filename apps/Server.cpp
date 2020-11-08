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

class CustomServer : public Sennet::Server<CustomMessageTypes>
{
public:
	CustomServer(uint16_t port) : Sennet::Server<CustomMessageTypes>(port)
	{
	}

protected:
	virtual bool OnClientConnect(
		Sennet::Ref<Sennet::Connection<CustomMessageTypes>> client)
		override 
	{
		return true;
	}

	virtual void OnClientDisconnect(
		Sennet::Ref<Sennet::Connection<CustomMessageTypes>>) 
		override
	{
	}

	virtual void OnMessage(
		Sennet::Ref<Sennet::Connection<CustomMessageTypes>> client,
		Sennet::Message<CustomMessageTypes>& message) 
		override
	{
		switch (message.Header.ID)
		{
		case CustomMessageTypes::ServerPing:
			SN_INFO("[{0}] Server Ping.", client->GetID());
			// Bounce message back to client.
			client->Send(message);
			break;
		}
	}
};

int main()
{
	Sennet::Log::Init();
	CustomServer server(60000);
	server.Start();

	while (true)
	{
		server.Update();
	}

	return 0;
}

#include <chrono>
#include <thread>

#include "Sennet/Sennet.hpp"

enum class DefaultMessageTypes: uint32_t
{
	ServerPing			= 0,
	ServerSynchronize	= 1,
	ServerAccept		= 2,
	ServerDeny			= 3,
};

class SynchronizationServer : public Sennet::Server<DefaultMessageTypes>
{
public:
	SynchronizationServer(uint16_t port) 
		: Sennet::Server<DefaultMessageTypes>(port)
	{
	}

	virtual ~SynchronizationServer()
	{
	}

protected:
	virtual bool OnClientConnect(
		Sennet::Ref<Sennet::Connection<DefaultMessageTypes>> client)
		override 
	{
		return true;
	}

	virtual void OnClientDisconnect(
		Sennet::Ref<Sennet::Connection<DefaultMessageTypes>>) 
		override
	{
	}

	virtual void OnMessage(
		Sennet::Ref<Sennet::Connection<DefaultMessageTypes>> client,
		Sennet::Message<DefaultMessageTypes>& message) 
		override
	{
		switch (message.Header.ID)
		{
		case DefaultMessageTypes::ServerPing:
			SN_INFO("[{0}] Server Ping.", client->GetID());
			// Bounce message back to client.
			client->Send(message);
			break;
		case DefaultMessageTypes::ServerSynchronize:
			SN_INFO("[{0}] Server Synchronize.", client->GetID());

			Sennet::Timestamp ts;
			ts.Grab();

			Sennet::Message<DefaultMessageTypes> reply;
			reply.Header.ID = 
				DefaultMessageTypes::ServerSynchronize;
			reply << ts.GetMilliseconds();
			client->Send(reply);
			break;
		}
	}
};

sig_atomic_t stopFlag = 0;

void interruptHandler(int)
{
	stopFlag = 1;
}

int main()
{
	// Set up interrupt handler.
	signal(SIGINT, &interruptHandler);
	uint32_t nodeRate = 60;

	Sennet::Log::Init();

	SynchronizationServer server(50000);
	server.Start();

	while (!stopFlag)
	{
		server.Update();
		std::this_thread::sleep_for(std::chrono::seconds(1 / nodeRate));
	}

	return 0;
}

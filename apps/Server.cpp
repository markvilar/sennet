#include <chrono>
#include <functional>
#include <thread>

#include <Sennet/Sennet.hpp>

class CustomServer : public Sennet::Server
{
public:
	CustomServer(uint16_t port) : Sennet::Server(port) {}

protected:
	virtual bool OnClientConnect(Sennet::Ref<Sennet::Connection> client) 
	{ 
		return true; 
	}
	
	virtual void OnClientDisconnect(Sennet::Ref<Sennet::Connection> client) 
	{
	}
	
	virtual void OnMessage(Sennet::Ref<Sennet::Connection> client, 
		Sennet::Ref<Sennet::Message> message) 
	{
	}
};

int main()
{
	Sennet::Log::Init();
	CustomServer server(6000);

	server.Start();
	while (true)
	{
		server.Update();
	}

	SN_INFO("Main finished.");
	return 0;
}

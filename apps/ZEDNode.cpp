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

class SensorLayer : public Sennet::Layer
{
	SensorLayer()
		: Layer("Sensor")
	{
	}

private:
	
};

class NetworkLayer : public Sennet::Layer
{
public:
	NetworkLayer(unsigned short port, uint64_t waitFor = 1)
		: Layer("Network"), m_Manager(port, waitFor)
	{
		SN_TRACE("Setting up connection manager.");
		m_Manager.SetMessageCallback(std::bind(
			&Sennet::Node::OnMessage, Sennet::Node::Get(), 
			std::placeholders::_1));
	}

	virtual void OnAttach() override
	{
		m_Manager.Start();
	}

	virtual void OnMessage(Sennet::Message& msg) override
	{
	}

private:

private:
	Sennet::ConnectionManager m_Manager;
};

class ZEDNode : public Sennet::Node
{
public:
	ZEDNode()
	{
		PushLayer(new NetworkLayer(7000, 1));
	}

private:
};

Sennet::Node* Sennet::CreateNode()
{
	return new ZEDNode();
}

int Sennet::main(int argc, char** argv)
{
	Sennet::Log::Init();
	auto node = Sennet::CreateNode();
	node->Run();
	return 0;
}

int main(int argc, char** argv)
{	
	return Sennet::main(argc, argv);
}

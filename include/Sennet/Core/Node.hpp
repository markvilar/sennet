#pragma once

#include <mutex>
#include <queue>

#include <Sennet/Core/Base.hpp>

#include <Sennet/Core/LayerStack.hpp>
#include <Sennet/Core/Timestep.hpp>

#include <Sennet/Messages/Message.hpp>
#include <Sennet/Network/ConnectionManager.hpp>

namespace Sennet
{

// TODO: Look into an alternative to Sennet::main function!
int main(int argc, char** argv);

class Node
{
public:
	Node(unsigned short port, uint64_t waitFor);
	virtual ~Node();

	void OnMessage(Ref<Message> msg);

	void PushLayer(Layer* layer);

	void Close();

	static Node& Get() { return *s_Instance; }

private:
	void Run();

protected:
	ConnectionManager m_ConnectionManager;

private:
	std::queue<Ref<Message>> m_MessageQueue;
	std::mutex m_Mutex;
	LayerStack m_LayerStack;
	bool m_Running = true;

private:
	static Node* s_Instance;
	friend int main(int argc, char** argv);
};

Node* CreateNode();

}

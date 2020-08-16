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
	Node(bool verbose = false);
	virtual ~Node();

	void OnMessage(Ref<Message> msg);

	void PushLayer(Layer* layer);

	void Close();

	static Node& Get() { return *s_Instance; }
	static Node* GetPtr() { return s_Instance; }

private:
	void Run();

private:
	LayerStack m_LayerStack;

	bool m_Running = true;

	// Temporary.
	std::queue<Ref<Message>> m_MessageQueue;
	std::mutex m_MessageMutex;
	bool m_Verbose;

private:
	static Node* s_Instance;
	friend int main(int argc, char** argv);
};

// To be defined by client.
Node* CreateNode();

}

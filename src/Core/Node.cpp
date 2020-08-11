#include <Sennet/pch.hpp>
#include <Sennet/Core/Node.hpp>

#include <Sennet/Core/Log.hpp>

namespace Sennet
{

Node* Node::s_Instance = nullptr;

Node::Node(unsigned short port, uint64_t waitFor)
	: m_ConnectionManager(port, waitFor),
	m_MessageQueue(),
	m_Mutex(),
	m_LayerStack()
{
	SN_CORE_ASSERT(!s_Instance, "Node already exists!");
	s_Instance = this;
	m_ConnectionManager.SetMessageCallback(std::bind(&Node::OnMessage, this, 
		std::placeholders::_1));
	m_ConnectionManager.Start();
}

Node::~Node()
{
}

void Node::OnMessage(Ref<Message> msg)
{
	SN_CORE_TRACE("Node: Got message {0}", msg->ToString());
	m_Mutex.lock();
	m_MessageQueue.push(msg);
	m_Mutex.unlock();
}

void Node::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Node::Close()
{
}

void Node::Run()
{
	SN_CORE_TRACE("Node: Running.");
	while (m_Running)
	{
		if (!m_MessageQueue.empty())
		{
			m_Mutex.lock();
			auto msg = m_MessageQueue.front();
			m_MessageQueue.pop();
			m_Mutex.unlock();

			// Propagate message through layers.
			for (Layer* layer : m_LayerStack)
			{
				layer->OnMessage(msg);
			}
		}
	}
}

}

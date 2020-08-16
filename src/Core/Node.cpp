#include <Sennet/pch.hpp>
#include <Sennet/Core/Node.hpp>

#include <Sennet/Core/Log.hpp>

namespace Sennet
{

Node* Node::s_Instance = nullptr;

Node::Node()
	: m_MessageQueue(), m_MessageMutex(), m_LayerStack()
{
	SN_CORE_ASSERT(!s_Instance, "Node already exists!");
	s_Instance = this;
}

Node::~Node()
{
}

void Node::OnMessage(Ref<Message> msg)
{
	m_MessageMutex.lock();
	m_MessageQueue.push(msg);
	m_MessageMutex.unlock();
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
	while (m_Running)
	{
		// Propagate messages through layers.
		while (!m_MessageQueue.empty())
		{
			m_MessageMutex.lock();
			auto msg = m_MessageQueue.front();
			m_MessageQueue.pop();
			m_MessageMutex.unlock();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnMessage(msg);
				if (msg->Handled)
					break;
			}
		}
	}
}

}

#include <Sennet/pch.hpp>
#include <Sennet/Core/Node.hpp>

#include <Sennet/Core/Log.hpp>

namespace Sennet
{

Node* Node::s_Instance = nullptr;

Node::Node(bool verbose)
	: m_MessageQueue(), m_MessageMutex(), m_LayerStack(),
	m_Verbose(verbose)
{
	SN_CORE_ASSERT(!s_Instance, "Node already exists!");
	s_Instance = this;
	SN_CORE_ASSERT(m_RunTimeout > 0, 
		"Node run timeout must be larger than zero!");
}

Node::~Node()
{
}

void Node::OnMessage(Ref<Message> msg)
{
	if (m_Verbose)
		SN_CORE_TRACE("Node: Got message {0}", msg->ToString());
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
	if (m_Verbose)
		SN_CORE_TRACE("Node: Running.");
	while (m_Running)
	{
		// Propagate messages through layers.
		while (!m_MessageQueue.empty())
		{
			m_MessageMutex.lock();
			auto msg = m_MessageQueue.front();
			m_MessageQueue.pop();
			m_MessageMutex.unlock();

			if (m_Verbose)
				SN_CORE_TRACE("Node: Propagating message {0}",
					msg->ToString());
			for (Layer* layer : m_LayerStack)
			{
				layer->OnMessage(msg);
				if (msg->Handled)
					break;
			}
		}

		// Sleep the main thread for a bit.
		std::this_thread::sleep_for(std::chrono::milliseconds(
			m_RunTimeout));
	}
	if (m_Verbose)
		SN_CORE_TRACE("Node: Stopped running.");
}

}

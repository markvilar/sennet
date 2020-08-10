#include <Sennet/pch.hpp>
#include <Sennet/Core/Node.hpp>

#include <Sennet/Core/Log.hpp>

namespace Sennet
{

Node* Node::s_Instance = nullptr;

Node::Node()
{
	SN_CORE_ASSERT(!s_Instance, "Node");
	s_Instance = this;
}

Node::~Node()
{
}

void Node::OnMessage(Ref<Message> msg)
{
	SN_CORE_TRACE("Node got message: {0}", msg->ToString());
	// TODO: Add to message queue?
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
		// Do stuff.
	}
}

}

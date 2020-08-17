#include <Sennet/pch.hpp>
#include <Sennet/Core/Application.hpp>

#include <GLFW/glfw3.h>

#include <Sennet/Core/Input.hpp>
#include <Sennet/Core/Log.hpp>
#include <Sennet/Core/Timestep.hpp>

#include <Sennet/Renderer/Renderer.hpp>

namespace Sennet
{

Application* Application::s_Instance = nullptr;

Application::Application(bool verbose)
	: m_Verbose(verbose)
{
	SN_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = Window::Create();
	m_Window->SetEventCallback(SN_BIND_EVENT_FN(Application::OnEvent));

	Renderer::Init();

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);
}

Application::~Application()
{
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(
		SN_BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(
		SN_BIND_EVENT_FN(Application::OnWindowResize));
	dispatcher.Dispatch<WindowIconifyEvent>(
		SN_BIND_EVENT_FN(Application::OnWindowIconify));

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
		{
			break;
		}
	}
}

void Application::OnMessage(Ref<Message> msg)
{
	if (m_Verbose)
		SN_CORE_TRACE("Application: Got message {0}.", msg->ToString());
	m_MessageMutex.lock();
	m_MessageQueue.push(msg);
	m_MessageMutex.unlock();
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
	m_LayerStack.PushOverlay(layer);
	layer->OnAttach();
}

void Application::Close()
{
}

void Application::Run()
{
	if (m_Verbose)
		SN_CORE_TRACE("Application: Running.");
	while (m_Running)
	{
		// Temporary.
		float time = glfwGetTime(); // Platform::GetTime
		Timestep ts = time - m_LastFrameTime;

		// Update layers.
		if (!m_Minimized)
		{
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(ts);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
		}
		
		m_Window->OnUpdate();

		// Propagate messages through layers.
		while (!m_MessageQueue.empty())
		{
			m_MessageMutex.lock();
			auto msg = m_MessageQueue.front();
			m_MessageQueue.pop();
			m_MessageMutex.unlock();
			
			if (m_Verbose)
			{
				SN_CORE_TRACE("Application: Propagating message {0}",
					msg->ToString());
			}

			for (Layer* layer : m_LayerStack)
			{
				layer->OnMessage(msg);
				if (msg->Handled)
					break;
			}
		}
	}

	if(m_Verbose)
		SN_CORE_TRACE("Application: Stopped running.");
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
	return false;
}

bool Application::OnWindowIconify(WindowIconifyEvent& e)
{
	m_Minimized = e.IsMinimized();
	return false;
}

};

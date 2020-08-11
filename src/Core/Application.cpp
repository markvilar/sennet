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

Application::Application()
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
	while (m_Running)
	{
		// Temporary.
		float time = glfwGetTime(); // Platform::GetTime
		Timestep ts = time - m_LastFrameTime;

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
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	SN_CORE_TRACE("Window Resize: {0}, {1}", e.GetWidth(), e.GetHeight());
	Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
	return false;
}

bool Application::OnWindowIconify(WindowIconifyEvent& e)
{
	SN_CORE_TRACE("Window Iconified: {0}", e.IsMinimized());
	m_Minimized = e.IsMinimized();
	return false;
}

};

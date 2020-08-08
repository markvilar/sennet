#include <Sennet/pch.hpp>
#include <Sennet/Core/Application.hpp>

#include <Sennet/Core/Log.hpp>
#include <Sennet/Core/Input.hpp>

namespace Sennet
{

Application* Application::s_Instance = nullptr;

Application::Application()
{
	SN_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = Window::Create();
	m_Window->SetEventCallback(SN_BIND_EVENT_FN(Application::OnEvent));

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);
}

Application::~Application()
{
}

void Application::OnEvent(Event& e)
{
	// Dispatch event.
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(
		SN_BIND_EVENT_FN(Application::OnWindowClose));

	// Propagate event through Layers.
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
		{
			break;
		}
	}
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

		for (Layer* layer : m_LayerStack)
		{
			layer->OnUpdate();
		}
		
		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
		{
			layer->OnImGuiRender();
		}
		m_ImGuiLayer->End();

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
	return true;
}

};

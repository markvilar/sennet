#pragma once

#include <Sennet/Core/Base.hpp>

#include <Sennet/Core/LayerStack.hpp>
#include <Sennet/Core/Timestep.hpp>
#include <Sennet/Core/Window.hpp>

#include <Sennet/Events/Event.hpp>
#include <Sennet/Events/ApplicationEvent.hpp>

#include <Sennet/ImGui/ImGuiLayer.hpp>

namespace Sennet
{

// TODO: Look into an alternative to Sennet::main function!
int main(int argc, char** argv);

class Application
{
public:
	Application();
	virtual ~Application();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);

	Window& GetWindow() { return *m_Window; }

	void Close();

	static Application& Get() { return *s_Instance; }

private:
	void Run();
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);

private:
	Scope<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	LayerStack m_LayerStack;
	bool m_Running = true;
	float m_LastFrameTime = 0.0f;

private:
	static Application* s_Instance;
	friend int main(int argc, char** argv);
};

// To be defined in client.
Application* CreateApplication();

}

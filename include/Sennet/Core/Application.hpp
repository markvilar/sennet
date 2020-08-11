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

	virtual void OnEvent(Event& e);
	virtual void OnMessage(Ref<Message> msg);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);

	Window& GetWindow() { return *m_Window; }

	void Close();

	static Application& Get() { return *s_Instance; }

private:
	virtual void Run();
	virtual bool OnWindowClose(WindowCloseEvent& e);
	virtual bool OnWindowResize(WindowResizeEvent& e);
	virtual bool OnWindowIconify(WindowIconifyEvent& e);

protected:
	Scope<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	LayerStack m_LayerStack;
	bool m_Running = true;
	bool m_Minimized = false;
	float m_LastFrameTime = 0.0f;

private:
	static Application* s_Instance;
	friend int main(int argc, char** argv);
};

// To be defined in client.
Application* CreateApplication();

}

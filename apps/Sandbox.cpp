#include <Sennet/Sennet.hpp>

#include <imgui.h>

class ExampleLayer : public Sennet::Layer
{
public:
	ExampleLayer()
		: Layer("example")
	{
	}

	void OnUpdate() override
	{
		if (Sennet::Input::IsKeyPressed(SN_KEY_TAB))
			SN_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world!");
		ImGui::End();
	}

	void OnEvent(Sennet::Event& event) override
	{
		if (event.GetEventType() == Sennet::EventType::KeyPressed)
		{
			Sennet::KeyPressedEvent& e =
				(Sennet::KeyPressedEvent&)event;
			
			if (e.GetKeyCode() == SN_KEY_TAB)
			{
				SN_TRACE("Tab key is pressed (event)!");
			}

			SN_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Sennet::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Sennet::Application* Sennet::CreateApplication()
{
	return new Sandbox();
}


int Sennet::main(int argc, char** argv)
{
	Sennet::Log::Init();

	auto app = Sennet::CreateApplication();
	app->Run();
	return 0;
}

int main(int argc, char** argv)
{	
	return Sennet::main(argc, argv);
}

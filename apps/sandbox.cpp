#include <sennet/sennet.hpp>

#include <imgui.h>

class example_layer : public sennet::layer
{
public:
	example_layer()
		: layer("example")
	{
	}

	void on_update() override
	{
		if (sennet::input::is_key_pressed(SN_KEY_TAB))
			SN_TRACE("Tab key is pressed (poll)!");
	}

	virtual void on_imgui_render() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world!");
		ImGui::End();
	}

	void on_event(sennet::event& event) override
	{
		if (event.get_event_type() == sennet::event_type::key_pressed)
		{
			sennet::key_pressed_event& e =
				(sennet::key_pressed_event&)event;
			
			if (e.get_key_code() == SN_KEY_TAB)
			{
				SN_TRACE("Tab key is pressed (event)!");
			}

			SN_TRACE("{0}", (char)e.get_key_code());
		}
	}
};

class sandbox : public sennet::application
{
public:
	sandbox()
	{
		push_layer(new example_layer());
	}

	~sandbox()
	{
	}
};

sennet::application* sennet::create_application()
{
	return new sandbox();
}


int sennet::main(int argc, char** argv)
{
	sennet::log::init();

	auto app = sennet::create_application();
	app->run();
	return 0;
}

int main(int argc, char** argv)
{	
	return sennet::main(argc, argv);
}

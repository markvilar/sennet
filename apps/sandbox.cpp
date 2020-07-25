#include <iostream>

#include <sl/Camera.hpp>

#include <imgui.h>

#include <sennet/sennet.hpp>

class example_layer : public sennet::layer
{
public:
	example_layer()
		: layer("example")
	{
	}

	void on_update() override
	{
		SN_INFO("example_layer::on_update");
	}

	void on_event(sennet::event& event) override
	{
		SN_TRACE("{0}", event.to_string());
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

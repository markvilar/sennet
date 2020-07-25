#include <iostream>

#include <sl/Camera.hpp>

#include <imgui.h>

#include <sennet/sennet.hpp>

int main()
{	
	sennet::log::init();

	sennet::application app;
	app.run();
	return 0;
}

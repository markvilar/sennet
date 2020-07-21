#include <iostream>

#include <sl/Camera.hpp>

#include <imgui.h>

#include <sennet/sennet.hpp>

int main()
{	
	sennet::log::init();

	auto window = sennet::window::create();
	SN_ASSERT(window, "Window is null!")

	return 0;
}

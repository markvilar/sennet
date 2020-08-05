#if defined(SN_PLATFORM_LINUX)

#include <sennet/pch.hpp>
#include <sennet/core/input.hpp>

#include <sennet/core/application.hpp>
#include <GLFW/glfw3.h>

namespace sennet
{

bool input::is_key_pressed(key_code key)
{
	auto window = static_cast<GLFWwindow*>(
		application::get().get_window().get_native_window());
	auto state = glfwGetKey(window, static_cast<int32_t>(key));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool input::is_mouse_button_pressed(mouse_code button)
{
	auto window = static_cast<GLFWwindow*>(
		application::get().get_window().get_native_window());
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
	return state == GLFW_PRESS;
}

std::pair<float, float> input::get_mouse_position()
{
	auto window = static_cast<GLFWwindow*>(
		application::get().get_window().get_native_window());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return { (float)xpos, (float)ypos };
}

float input::get_mouse_x()
{
	return get_mouse_position().first;
}

float input::get_mouse_y()
{
	return get_mouse_position().second;
}

}

#endif

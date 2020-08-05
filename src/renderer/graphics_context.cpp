#include <sennet/pch.hpp>
#include <sennet/renderer/graphics_context.hpp>

#include <sennet/platform/opengl/opengl_context.hpp>

namespace sennet
{

scope<graphics_context> graphics_context::create(void* window)
{
	// TODO: Add support for different renderer APIs later?
	return create_scope<opengl_context>(static_cast<GLFWwindow*>(window));
}

}

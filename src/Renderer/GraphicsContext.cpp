#include <Sennet/pch.hpp>
#include <Sennet/Renderer/GraphicsContext.hpp>

#include <Sennet/Platform/OpenGL/OpenGLContext.hpp>

namespace Sennet
{

Scope<GraphicsContext> GraphicsContext::Create(void* window)
{
	// TODO: Add support for different renderer APIs later?
	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
}

}

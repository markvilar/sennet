#include "Sennet/Pch.hpp"
#include "Sennet/Renderer/GraphicsContext.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

namespace Sennet
{

Scope<GraphicsContext> GraphicsContext::Create(void* window)
{
	// TODO: Add support for different renderer APIs later?
	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
}

}

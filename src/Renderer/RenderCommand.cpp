#include <Sennet/pch.hpp>
#include <Sennet/Renderer/RenderCommand.hpp>

#include <Sennet/Platform/OpenGL/OpenGLRendererAPI.hpp>

namespace Sennet
{

RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}

#include <Sennet/pch.hpp>
#include <Sennet/Renderer/VertexArray.hpp>

#include <Sennet/Renderer/Renderer.hpp>
#include <Sennet/Renderer/RendererAPI.hpp>
#include <Sennet/Platform/OpenGL/OpenGLVertexArray.hpp>

namespace Sennet
{

VertexArray* VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: 
			SN_CORE_ASSERT(false, "renderer_api::none is currently \
				not supported!");
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
	}
	
	SN_CORE_ASSERT(false, "Unknown renderer API.");
	return nullptr;
}

}

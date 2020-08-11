#include <Sennet/pch.hpp>
#include <Sennet/Renderer/VertexArray.hpp>

#include <Sennet/Renderer/Renderer.hpp>

#include <Sennet/Platform/OpenGL/OpenGLVertexArray.hpp>

namespace Sennet
{

Ref<VertexArray> VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: 
			SN_CORE_ASSERT(false, "Renderer API None is currently \
				not supported!");
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
	}
	
	SN_CORE_ASSERT(false, "Unknown Renderer API.");
	return nullptr;
}

}

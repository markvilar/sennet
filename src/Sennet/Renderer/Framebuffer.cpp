#include "Sennet/Pch.hpp"
#include "Sennet/Renderer/Framebuffer.hpp"

#include "Sennet/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLFramebuffer.hpp"

namespace Sennet
{

Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
{
	switch(Renderer::GetAPI())
	{
		case RendererAPI::API::None:
			SN_CORE_ASSERT(false, "RendererAPI::None is currently not "
				"supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFramebuffer>(spec);
	}

	SN_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

}

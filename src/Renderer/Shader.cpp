#include <Sennet/pch.hpp>
#include <Sennet/Renderer/Shader.hpp>

#include <Sennet/Renderer/Renderer.hpp>
#include <Sennet/Renderer/RendererAPI.hpp>

#include <Sennet/Platform/OpenGL/OpenGLShader.hpp>

namespace Sennet
{

Shader* Shader::Create(const std::string& vertexSrc, 
	const std::string& fragmentSrc)
{
	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: 
			SN_CORE_ASSERT(false, "Renderer API None is currently \
				not supported!");
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
	}
	
	SN_CORE_ASSERT(false, "Unknown Renderer API.");
	return nullptr;

}

}

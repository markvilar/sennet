#pragma once
#include <Sennet/pch.hpp>

namespace Sennet
{

class Shader
{
public:
	Shader(const std::string& vertex_src, const std::string& fragment_src);
	~Shader();

	void Bind() const;
	void Unbind() const;

private:
	uint32_t m_RendererID;
};

}
#pragma once
#include <sennet/pch.hpp>

namespace sennet
{

class shader
{
public:
	shader(const std::string& vertex_src, const std::string& fragment_src);
	~shader();

	void bind() const;
	void unbind() const;

private:
	uint32_t m_renderer_id;
};

}

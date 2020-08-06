#include <sennet/pch.hpp>
#include <sennet/renderer/buffer.hpp>

#include <sennet/renderer/renderer.hpp>

#include <sennet/platform/opengl/opengl_buffer.hpp>

namespace sennet
{

std::string buffer_layout::to_string() const
{
	std::stringstream ss;
	ss << "\nstride: " << m_stride << "\n";
	for (auto& element : m_elements)
	{
		ss << "name: " << element.name 
			<< ", type: " << ::sennet::to_string(element.type)
			<< ", size: " << element.size
			<< ", offset: " << element.offset
			<< "\n";
	}
	return ss.str();
}


void buffer_layout::calculate_offset_and_stride()
{
	uint32_t offset = 0;
	m_stride = 0;
	for (auto& element : m_elements)
	{
		element.offset = offset;
		offset += element.size;
		m_stride += element.size;
	}
}

vertex_buffer* vertex_buffer::create(float* vertices, uint32_t size)
{
	switch (renderer::get_api())
	{
		case renderer_api::none: 
			SN_CORE_ASSERT(false, "renderer_api::none is currently \
				not supported!");
		case renderer_api::opengl:
			return new opengl_vertex_buffer(vertices, size);
	}
	
	SN_CORE_ASSERT(false, "Unknown renderer API.");
	return nullptr;
}

index_buffer* index_buffer::create(uint32_t* indices, uint32_t count)
{
	switch (renderer::get_api())
	{
		case renderer_api::none: 
			SN_CORE_ASSERT(false, "Renderer API none is currently \
				not supported!");
		case renderer_api::opengl:
			return new opengl_index_buffer(indices, count);
	}
	
	SN_CORE_ASSERT(false, "Unknown renderer API.");
	return nullptr;
}

}

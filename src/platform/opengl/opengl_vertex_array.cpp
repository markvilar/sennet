#include <sennet/pch.hpp>
#include <sennet/platform/opengl/opengl_vertex_array.hpp>

#include <glad/glad.h>

namespace sennet
{

static GLenum shader_data_type_2_opengl_base_type(shader_data_type type)
{
	switch (type)
	{
		case shader_data_type::Float: 	return GL_FLOAT;
		case shader_data_type::Float2: 	return GL_FLOAT;
		case shader_data_type::Float3: 	return GL_FLOAT;
		case shader_data_type::Float4: 	return GL_FLOAT;
		case shader_data_type::Mat3: 	return GL_FLOAT;
		case shader_data_type::Mat4: 	return GL_FLOAT;
		case shader_data_type::Int: 	return GL_INT;
		case shader_data_type::Int2: 	return GL_INT;
		case shader_data_type::Int3: 	return GL_INT;
		case shader_data_type::Int4: 	return GL_INT;
		case shader_data_type::Bool: 	return GL_BOOL;
		case shader_data_type::None:	return 0;
	}

	SN_CORE_ASSERT(false, "Unknown shader_data_type!");
	return 0;
}

opengl_vertex_array::opengl_vertex_array()
{
	glCreateVertexArrays(1, &m_renderer_id);
}

void opengl_vertex_array::bind() const
{
	glBindVertexArray(m_renderer_id);
}

void opengl_vertex_array::unbind() const
{
	glBindVertexArray(0);
}

void opengl_vertex_array::add_vertex_buffer(const ref<vertex_buffer>& buffer)
{
	glBindVertexArray(m_renderer_id);
	buffer->bind();

	SN_CORE_ASSERT(buffer->get_layout().get_elements().size(),
		"Vertex Buffer has no layout!")

	uint32_t index = 0;
	const auto& layout = buffer->get_layout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 
			element.get_component_count(), 
			shader_data_type_2_opengl_base_type(element.type), 
			element.normalized ? GL_TRUE : GL_FALSE, 
			layout.get_stride(), 
			(const void*)element.offset);
		index++;
	}

	m_vertex_buffers.push_back(buffer);
}

void opengl_vertex_array::set_index_buffer(const ref<index_buffer>& buffer)
{
	glBindVertexArray(m_renderer_id);
	buffer->bind();

	m_index_buffer = buffer;
}

}

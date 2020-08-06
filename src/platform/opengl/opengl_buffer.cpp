#include <sennet/pch.hpp>
#include <sennet/platform/opengl/opengl_buffer.hpp>

#include <glad/glad.h>

namespace sennet
{

///////////////////////////////////////////////////////////////////////////////
// Vertex Buffer //////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


opengl_vertex_buffer::opengl_vertex_buffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &m_renderer_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

opengl_vertex_buffer::~opengl_vertex_buffer()
{
	glDeleteBuffers(1, &m_renderer_id);
}

void opengl_vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}

void opengl_vertex_buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

///////////////////////////////////////////////////////////////////////////////
// Index Buffer ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

opengl_index_buffer::opengl_index_buffer(uint32_t* indices, uint32_t count)
	: m_count(count)
{
	glCreateBuffers(1, &m_renderer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices,
		GL_STATIC_DRAW);
}

opengl_index_buffer::~opengl_index_buffer()
{
	glDeleteBuffers(1, &m_renderer_id);
}

void opengl_index_buffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

void opengl_index_buffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

}

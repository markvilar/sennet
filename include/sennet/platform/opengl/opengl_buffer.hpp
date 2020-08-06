#pragma once
#include <sennet/renderer/buffer.hpp>

namespace sennet
{

class opengl_vertex_buffer : public vertex_buffer
{
public:
	opengl_vertex_buffer(float* vertices, uint32_t size);
	virtual ~opengl_vertex_buffer();

	virtual void bind() const override;
	virtual void unbind() const override;

private:
	uint32_t m_renderer_id;
};

class opengl_index_buffer : public index_buffer
{
public:
	opengl_index_buffer(uint32_t* indices, uint32_t count);
	virtual ~opengl_index_buffer();

	virtual void bind() const override;
	virtual void unbind() const override;

	virtual uint32_t get_count() const override { return m_count; }

private:
	uint32_t m_renderer_id;
	uint32_t m_count;
};


}

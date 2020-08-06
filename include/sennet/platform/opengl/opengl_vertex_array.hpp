#pragma once

#include <sennet/renderer/vertex_array.hpp>

namespace sennet
{

class opengl_vertex_array : public vertex_array
{
	typedef std::vector<ref<vertex_buffer>> vertex_buffer_vec;
public:
	opengl_vertex_array();
	virtual ~opengl_vertex_array();

	virtual void bind() const override;
	virtual void unbind() const override;

	virtual void add_vertex_buffer(const ref<vertex_buffer>& buffer) override;
	virtual void set_index_buffer(const ref<index_buffer>& buffer) override;

	virtual const vertex_buffer_vec& get_vertex_buffers() const override
	{
		return m_vertex_buffers;
	}

	virtual const ref<index_buffer>& get_index_buffer() const override
	{
		return m_index_buffer;
	}

private:
	uint32_t m_renderer_id;
	vertex_buffer_vec m_vertex_buffers;
	ref<index_buffer> m_index_buffer;
};

}

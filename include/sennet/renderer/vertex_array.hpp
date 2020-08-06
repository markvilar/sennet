#pragma once

#include <sennet/core/base.hpp>
#include <sennet/renderer/buffer.hpp>

namespace sennet
{

class vertex_array
{
	typedef std::vector<ref<vertex_buffer>> vertex_buffer_vec;
public:
	virtual ~vertex_array() {}

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual void add_vertex_buffer(const ref<vertex_buffer>& buffer) = 0;
	virtual void set_index_buffer(const ref<index_buffer>& buffer) = 0;

	virtual const vertex_buffer_vec& get_vertex_buffers() const = 0;
	virtual const ref<index_buffer>& get_index_buffer() const = 0;

	static vertex_array* create();
};

}

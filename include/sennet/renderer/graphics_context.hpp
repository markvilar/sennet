#pragma once

#include <sennet/core/base.hpp>

namespace sennet
{

class graphics_context
{
public:
	virtual ~graphics_context() = default;

	virtual void init() = 0;
	virtual void swap_buffers() = 0;

	static scope<graphics_context> create(void* window);
};

}

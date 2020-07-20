#pragma once

#include <sennet/renderer/graphics_context.hpp>

// Forward declaration.
struct GLFWwindow;

namespace sennet
{

class opengl_context : public graphics_context
{
public:
	opengl_context(GLFWwindow* window_handle);

	virtual void init() override;
	virtual void swap_buffers() override;

private:
	GLFWwindow* m_window_handle;
};

}

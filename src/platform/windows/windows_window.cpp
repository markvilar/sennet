#include <sennet/snpch.hpp>
#include <sennet/platform/windows/windows_window.hpp>

#include <sennet/core/input.hpp>

#include <sennet/events/application_event.hpp>
#include <sennet/events/key_event.hpp>
#include <sennet/events/mouse_event.hpp>

#include <sennet/platform/opengl/opengl_context.hpp>

namespace sennet
{

static uint8_t s_glfw_window_count = 0;

static void glfw_error_callback(int error, const char* description)
{
	SN_CORE_ERROR("GLFW error ({0}): {1}", error, description);
}

windows_window::windows_window(const window_props& props)
{
	init(props);
}

windows_window::~windows_window()
{
	shutdown();
}

void windows_window::init(const window_props& props)
{
	m_data.title = props.title;
	m_data.width = props.width;
	m_data.height = props.height;

	SN_CORE_INFO("Creating window {0}, ({1}, {2})", props.title, 
		props.width, props.height);
	
	if (s_glfw_window_count == 0)
	{
		int success = glfwInit();
		SN_CORE_ASSERT(success, "Could not initialize GLFW!");
	}
	
	{
	#if defined(SN_DEBUG)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	#endif
		m_window = glfwCreateWindow((int)props.width, (int)props.height,
			m_data.title.c_str(), nullptr, nullptr);
		++s_glfw_window_count;
	}

	m_context = graphics_context::create(m_window);
	m_context->init();

	glfwSetWindowSizeCallback(m_window, 
		[](GLFWwindow* window, int width, int height)
		{
			window_data& data =
				*(window_data*)glfwGetWindowUserPointer(window);
			data.width= width;
			data.height= height;

			window_resize_event event(width, height);
			data.event_callback(event);
		});
	
	// TODO: Implement the rest!
}

void windows_window::shutdown()
{
	SN_CORE_INFO("Deleting window {0}, ({1}, {2})", m_data.title,
		m_data.width, m_data.height);
}

void windows_window::on_update()
{
	// TODO: Implement.
}

void windows_window::set_vsync(bool enabled)
{
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{
		glfwSwapInterval(0);
	}

	m_data.vsync = enabled;
}

bool windows_window::is_vsync() const
{
	return m_data.vsync;
}

}

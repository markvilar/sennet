#include <sennet/pch.hpp>
#include <sennet/platform/linux/linux_window.hpp>

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

linux_window::linux_window(const window_props& props)
{
	init(props);
}

linux_window::~linux_window()
{
	shutdown();
}

void linux_window::on_update()
{
	glfwPollEvents();
	m_context->swap_buffers();
}

void linux_window::set_vsync(bool enabled)
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

bool linux_window::is_vsync() const
{
	return m_data.vsync;
}

void linux_window::init(const window_props& props)
{
	m_data.title = props.title;
	m_data.width = props.width;
	m_data.height = props.height;

	SN_CORE_INFO("Creating window {0}, ({1}, {2})", props.title, 
		props.width, props.height);
	
	if (s_glfw_window_count == 0)
	{
		SN_CORE_INFO("Initializing GLFW.");
		int success = glfwInit();
		SN_CORE_ASSERT(success, "Could not initialize GLFW!");
		glfwSetErrorCallback(glfw_error_callback);
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

	glfwSetWindowUserPointer(m_window, &m_data);
	set_vsync(true);

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
	
	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
	{
		window_data& data =
			*(window_data*)glfwGetWindowUserPointer(window);
		window_close_event event;
		data.event_callback(event);
	});

	glfwSetKeyCallback(m_window, 
		[](GLFWwindow* window, int key, int scancode, int action, 
		int mods)
	{
		window_data& data = 
			*(window_data*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				key_pressed_event event(
					static_cast<key_code>(key), 0);
				data.event_callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				key_released_event event(
					static_cast<key_code>(key));
				data.event_callback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				key_pressed_event event(
					static_cast<key_code>(key), 1);
				data.event_callback(event);
				break;
			}
		}
	});
	
	glfwSetCharCallback(m_window,
		[](GLFWwindow* window, unsigned int keycode)
	{
		window_data& data =
			*(window_data*)glfwGetWindowUserPointer(window);
		key_typed_event event(static_cast<key_code>(keycode));
		data.event_callback(event);
	});

	glfwSetMouseButtonCallback(m_window,
		[](GLFWwindow* window, int button, int action, int mods)
	{
		window_data& data =
			*(window_data*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				mouse_button_pressed_event event(
					static_cast<mouse_code>(button));
				data.event_callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				mouse_button_released_event event(
					static_cast<mouse_code>(button));
				data.event_callback(event);
				break;
			}
		}
	});

	glfwSetScrollCallback(m_window,
		[](GLFWwindow* window, double x_offset, double y_offset)
	{
		window_data& data = 
			*(window_data*)glfwGetWindowUserPointer(window);
		
		mouse_scrolled_event event((float)x_offset, (float)y_offset);
		data.event_callback(event);
	});

	glfwSetCursorPosCallback(m_window,
		[](GLFWwindow* window, double x_pos, double y_pos)
	{
		window_data& data =
			*(window_data*)glfwGetWindowUserPointer(window);
		
		mouse_moved_event event((float)x_pos, (float)y_pos);
		data.event_callback(event);
	});
}

void linux_window::shutdown()
{
	SN_CORE_INFO("Deleting window {0}, ({1}, {2})", m_data.title,
		m_data.width, m_data.height);

	glfwDestroyWindow(m_window);
	--s_glfw_window_count;

	if (s_glfw_window_count == 0)
	{
		SN_CORE_INFO("Terminating GLFW");
		glfwTerminate();
	}
}

}

#pragma once

#include <GLFW/glfw3.h>

#include <sennet/core/window.hpp>
#include <sennet/renderer/graphics_context.hpp>

namespace sennet
{

class linux_window : public window
{
public:
	linux_window(const window_props& props);
	virtual ~linux_window();

	void on_update() override;

	unsigned int get_width() const override { return m_data.width; }
	unsigned int get_height() const override { return m_data.height; }

	// Window attributes.
	void set_event_callback (const event_callback_fn& callback) override
	{
		m_data.event_callback = callback;
	}
	void set_vsync(bool enabled) override;
	bool is_vsync() const override;

	virtual void* get_native_window() const { return m_window; }

private:
	virtual void init(const window_props& props);
	virtual void shutdown();

private:
	GLFWwindow* m_window;
	scope<graphics_context> m_context;

	struct window_data
	{
		std::string title;
		unsigned int width;
		unsigned int height;
		bool vsync;

		event_callback_fn event_callback;
	};

	window_data m_data;
};

}

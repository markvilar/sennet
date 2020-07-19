#pragma once

#include <sennet/snpch.hpp>

#include <sennet/core/base.hpp>
#include <sennet/events/event.hpp>

namespace sennet
{

struct window_props
{
	std::string m_title;
	uint32_t m_width;
	uint32_t m_height;

	window_props(const std::string& title = "Sennet GUI",
		uint32_t width = 1280,
		uint32_t height = 720)
		: m_title(title), m_width(width), m_height(height)
	{
	}
};

class window
{
	// Interface representing a desktop system based window.

public:
	using event_callback_fn = std::function<void(event&)>;

	virtual ~window() = default;

	virtual void on_update() = 0;

	virtual uint32_t get_width() const = 0;
	virtual uint32_t get_height() const = 0;

	virtual void set_event_callback(const event_callback_fn& callback) = 0;
	virtual void set_vsync(bool enabled) = 0;
	virtual bool is_vsync() const = 0;

	virtual void* get_native_window() const = 0;

	static scope<window> create(
		const window_props& props = window_props());
};

}

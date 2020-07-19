#pragma once

#include <sennet/snpch.hpp>

#include <sennet/core/base.hpp>

namespace sennet
{

enum class event_type
{
	none = 0, 
	window_close, window_resize, window_focus, window_lost_focus, 
	window_moved,
	app_tick, app_update, app_render, 
	key_pressed, key_released, key_typed,
	mouse_button_pressed, mouse_button_released, mouse_moved, mouse_scrolled
};

enum event_category
{
	none = 0,
	event_category_application = BIT(0),
	event_category_input = BIT(1),
	event_category_keyboard = BIT(2),
	event_category_mouse = BIT(3),
	event_category_mouse_button = BIT(4)
};

#define EVENT_CLASS_TYPE(type) 						\
	static event_type get_static_type()				\
	{ return event_type::type; }					\
	virtual event_type get_event_type() const override		\
	{ return return get_static_type(); }				\
	virtual const char* get_name() const override 			\
	{ return #type; }						

#define EVENT_CLASS_CATEGORY(category)					\
	virtual int get_category_flags() const override 		\
	{ return category; }

class event
{
public:
	virtual ~event() = default;

	bool handled = false;

	virtual event_type get_event_type() const = 0;
	virtual const char* get_name() const = 0;
	virtual int get_category_flags() const = 0;
	virtual std::string to_string() const { return get_name(); }

	bool is_in_category(event_category category)
	{
		// Bitwise AND operator.
		return get_category_flags() & category;
	}
};

class event_dispatcher
{
public:
	event_dispatcher(event& e)
		: m_event(e)
	{
	}

	// F will be deduced by the compiler.
	template<typename T, typename F>
	bool dispatch(const F& func)
	{
		if (m_event.get_event_type() == T::get_static_type())
		{
			m_event.handled = func(static_cast<T&>(m_event));
			return true;
		}
		return false;
	}

private:
	event& m_event;
};

inline std::ostream& operator<<(std::ostream& os, event& e)
{
	return os << e.to_string();
}

};

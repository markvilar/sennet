#pragma once

#include <sennet/core/input.hpp>
#include <sennet/events/event.hpp>

namespace sennet
{

class key_event : public event
{
public:
	key_code get_key_code() const { return m_key_code; }

	EVENT_CLASS_CATEGORY(event_category_keyboard | event_category_input)

protected:
	key_event(const key_code code)
		: m_key_code(code) {}

	key_code m_key_code;
};

class key_pressed_event : public key_event
{
public:
	key_pressed_event(const key_code code, const int repeat_count)
		: key_event(code), m_repeat_count(repeat_count) {}

	int get_repeat_count() const { return m_repeat_count; }

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "[key_pressed_event] " << m_key_code << " ("
			<< m_repeat_count << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(key_pressed)

private:
	int m_repeat_count;
};

class key_released_event : public key_event
{
public:
	key_released_event(const key_code code)
		: key_event(code) {}
	
	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "[key_released_event] " << m_key_code;
		return ss.str();
	}

	EVENT_CLASS_TYPE(key_released)
};

class key_typed_event : public key_event
{
public:
	key_typed_event(const key_code code)
		: key_event(code) {}
	
	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "[key_typed_event] " << m_key_code;
		return ss.str();
	}

	EVENT_CLASS_TYPE(key_typed)
};

}

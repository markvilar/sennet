#pragma once

#include <sennet/core/base.hpp>
#include <sennet/core/key_codes.hpp>
#include <sennet/core/mouse_codes.hpp>

namespace sennet
{

class input
{
public:
	static bool is_key_pressed(key_code key);

	static bool is_mouse_button_pressed(mouse_code button);
	static std::pair<float, float> get_mouse_position();
	static float get_mouse_x();
	static float get_mouse_y();
};

}

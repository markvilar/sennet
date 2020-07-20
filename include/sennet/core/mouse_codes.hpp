#pragma once

namespace sennet
{

typedef enum class mouse_code : uint16_t
{
	// From glfw3.h
	button_0               = 0,
	button_1               = 1,
	button_2               = 2,
	button_3               = 3,
	button_4               = 4,
	button_5               = 5,
	button_6               = 6,
	button_7               = 7,

	button_last            = button_7,
	button_left            = button_0,
	button_right           = button_1,
	button_middle          = button_2
} mouse;

inline std::ostream& operator<<(std::ostream& os, const mouse_code code)
{
	return os << static_cast<int32_t>(code);
}

}

#define SN_MOUSE_BUTTON_0      ::sennet::mouse::button_0
#define SN_MOUSE_BUTTON_1      ::sennet::mouse::button_1
#define SN_MOUSE_BUTTON_2      ::sennet::mouse::button_2
#define SN_MOUSE_BUTTON_3      ::sennet::mouse::button_3
#define SN_MOUSE_BUTTON_4      ::sennet::mouse::button_4
#define SN_MOUSE_BUTTON_5      ::sennet::mouse::button_5
#define SN_MOUSE_BUTTON_6      ::sennet::mouse::button_6
#define SN_MOUSE_BUTTON_7      ::sennet::mouse::button_7
#define SN_MOUSE_BUTTON_LAST   ::sennet::mouse::button_last
#define SN_MOUSE_BUTTON_LEFT   ::sennet::mouse::button_left
#define SN_MOUSE_BUTTON_RIGHT  ::sennet::mouse::button_right
#define SN_MOUSE_BUTTON_MIDDLE ::sennet::mouse::button_middle

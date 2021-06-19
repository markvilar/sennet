#pragma once

namespace Sennet
{

typedef enum class MouseCode : uint16_t
{
	// From glfw3.h
	Button0               = 0,
	Button1               = 1,
	Button2               = 2,
	Button3               = 3,
	Button4               = 4,
	Button5               = 5,
	Button6               = 6,
	Button7               = 7,

	Buttonlast            = Button7,
	Buttonleft            = Button0,
	Buttonright           = Button1,
	Buttonmiddle          = Button2
} Mouse;

inline std::ostream& operator<<(std::ostream& os, const MouseCode mouseCode)
{
	return os << static_cast<int32_t>(mouseCode);
}

}

#define SN_MOUSE_BUTTON_0      ::Sennet::Mouse::Button0
#define SN_MOUSE_BUTTON_1      ::Sennet::Mouse::Button1
#define SN_MOUSE_BUTTON_2      ::Sennet::Mouse::Button2
#define SN_MOUSE_BUTTON_3      ::Sennet::Mouse::Button3
#define SN_MOUSE_BUTTON_4      ::Sennet::Mouse::Button4
#define SN_MOUSE_BUTTON_5      ::Sennet::Mouse::Button5
#define SN_MOUSE_BUTTON_6      ::Sennet::Mouse::Button6
#define SN_MOUSE_BUTTON_7      ::Sennet::Mouse::Button7
#define SN_MOUSE_BUTTON_LAST   ::Sennet::Mouse::ButtonLast
#define SN_MOUSE_BUTTON_LEFT   ::Sennet::Mouse::ButtonLeft
#define SN_MOUSE_BUTTON_RIGHT  ::Sennet::Mouse::ButtonRight
#define SN_MOUSE_BUTTON_MIDDLE ::Sennet::Mouse::ButtonMiddle

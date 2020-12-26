#pragma once

namespace Sennet
{

typedef enum class KeyCode : uint16_t
{
	Space               = 32,
	Apostrophe          = 39, /* ' */
	Comma               = 44, /* , */
	Minus               = 45, /* - */
	Period              = 46, /* . */
	Slash               = 47, /* / */

	D0                  = 48, /* 0 */
	D1                  = 49, /* 1 */
	D2                  = 50, /* 2 */
	D3                  = 51, /* 3 */
	D4                  = 52, /* 4 */
	D5                  = 53, /* 5 */
	D6                  = 54, /* 6 */
	D7                  = 55, /* 7 */
	D8                  = 56, /* 8 */
	D9                  = 57, /* 9 */

	Semicolon           = 59, /* ; */
	Equal               = 61, /* = */

	A                   = 65,
	B                   = 66,
	C                   = 67,
	D                   = 68,
	E                   = 69,
	F                   = 70,
	G                   = 71,
	H                   = 72,
	I                   = 73,
	J                   = 74,
	K                   = 75,
	L                   = 76,
	M                   = 77,
	N                   = 78,
	O                   = 79,
	P                   = 80,
	Q                   = 81,
	R                   = 82,
	S                   = 83,
	T                   = 84,
	U                   = 85,
	V                   = 86,
	W                   = 87,
	X                   = 88,
	Y                   = 89,
	Z                   = 90,

	LeftBracket         = 91,  /* [ */
	Backslash	    = 92,  /* \ */
	RightBracket 	    = 93,  /* ] */
	GraveAccent         = 96,  /* ` */

	World1              = 161, /* non-US #1 */
	World2              = 162, /* non-US #2 */

	/* Function keys */
	Escape              = 256,
	Enter               = 257,
	Tab                 = 258,
	Backspace           = 259,
	Insert              = 260,
	Del                 = 261,
	Right               = 262,
	Left                = 263,
	Down                = 264,
	Up                  = 265,
	PageUp              = 266,
	PageDown            = 267,
	Home                = 268,
	End                 = 269,
	CapsLock            = 280,
	ScrollLock          = 281,
	NumLock             = 282,
	PrintScreen         = 283,
	Pause               = 284,
	F1                  = 290,
	F2                  = 291,
	F3                  = 292,
	F4                  = 293,
	F5                  = 294,
	F6                  = 295,
	F7                  = 296,
	F8                  = 297,
	F9                  = 298,
	F10                 = 299,
	F11                 = 300,
	F12                 = 301,
	F13                 = 302,
	F14                 = 303,
	F15                 = 304,
	F16                 = 305,
	F17                 = 306,
	F18                 = 307,
	F19                 = 308,
	F20                 = 309,
	F21                 = 310,
	F22                 = 311,
	F23                 = 312,
	F24                 = 313,
	F25                 = 314,

	/* keypad */
	KP0                = 320,
	KP1                = 321,
	KP2                = 322,
	KP3                = 323,
	KP4                = 324,
	KP5                = 325,
	KP6                = 326,
	KP7                = 327,
	KP8                = 328,
	KP9                = 329,
	KPDecimal          = 330,
	KPDivide           = 331,
	KPMultiply         = 332,
	KPSubtract         = 333,
	KPAdd              = 334,
	KPEnter            = 335,
	KPEqual            = 336,

	LeftShift          = 340,
	LeftControl        = 341,
	LeftAlt            = 342,
	LeftSuper          = 343,
	RightShift         = 344,
	RightControl       = 345,
	RightAlt           = 346,
	RightSuper         = 347,
	Menu               = 348
} Key;

inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
{
	return os << static_cast<int32_t>(keyCode);
}

}

// From glfw3.h
#define SN_KEY_SPACE           ::Sennet::Key::Space
#define SN_KEY_APOSTROPHE      ::Sennet::Key::Apostrophe    /* ' */
#define SN_KEY_COMMA           ::Sennet::Key::Comma         /* , */
#define SN_KEY_MINUS           ::Sennet::Key::Minus         /* - */
#define SN_KEY_PERIOD          ::Sennet::Key::Period        /* . */
#define SN_KEY_SLASH           ::Sennet::Key::Slash         /* / */
#define SN_KEY_0               ::Sennet::Key::D0
#define SN_KEY_1               ::Sennet::Key::D1
#define SN_KEY_2               ::Sennet::Key::D2
#define SN_KEY_3               ::Sennet::Key::D3
#define SN_KEY_4               ::Sennet::Key::D4
#define SN_KEY_5               ::Sennet::Key::D5
#define SN_KEY_6               ::Sennet::Key::D6
#define SN_KEY_7               ::Sennet::Key::D7
#define SN_KEY_8               ::Sennet::Key::D8
#define SN_KEY_9               ::Sennet::Key::D9
#define SN_KEY_SEMICOLON       ::Sennet::Key::Semicolon     /* ; */
#define SN_KEY_EQUAL           ::Sennet::Key::Equal         /* = */
#define SN_KEY_A               ::Sennet::Key::A
#define SN_KEY_B               ::Sennet::Key::B
#define SN_KEY_C               ::Sennet::Key::C
#define SN_KEY_D               ::Sennet::Key::D
#define SN_KEY_E               ::Sennet::Key::E
#define SN_KEY_F               ::Sennet::Key::F
#define SN_KEY_G               ::Sennet::Key::G
#define SN_KEY_H               ::Sennet::Key::H
#define SN_KEY_I               ::Sennet::Key::I
#define SN_KEY_J               ::Sennet::Key::J
#define SN_KEY_K               ::Sennet::Key::K
#define SN_KEY_L               ::Sennet::Key::L
#define SN_KEY_M               ::Sennet::Key::M
#define SN_KEY_N               ::Sennet::Key::N
#define SN_KEY_O               ::Sennet::Key::O
#define SN_KEY_P               ::Sennet::Key::P
#define SN_KEY_Q               ::Sennet::Key::Q
#define SN_KEY_R               ::Sennet::Key::R
#define SN_KEY_S               ::Sennet::Key::S
#define SN_KEY_T               ::Sennet::Key::T
#define SN_KEY_U               ::Sennet::Key::U
#define SN_KEY_V               ::Sennet::Key::V
#define SN_KEY_W               ::Sennet::Key::W
#define SN_KEY_X               ::Sennet::Key::X
#define SN_KEY_Y               ::Sennet::Key::Y
#define SN_KEY_Z               ::Sennet::Key::Z
#define SN_KEY_LEFT_BRACKET    ::Sennet::Key::LeftBracket   /* [ */
#define SN_KEY_BACKSLASH       ::Sennet::Key::Backslash     /* \ */
#define SN_KEY_RIGHT_BRACKET   ::Sennet::Key::RightBracket  /* ] */
#define SN_KEY_GRAVE_ACCENT    ::Sennet::Key::GraveAccent   /* ` */
#define SN_KEY_WORLD_1         ::Sennet::Key::World1        /* non-US #1 */
#define SN_KEY_WORLD_2         ::Sennet::Key::World2        /* non-US #2 */

/* Function keys */
#define SN_KEY_ESCAPE          ::Sennet::Key::Escape
#define SN_KEY_ENTER           ::Sennet::Key::Enter
#define SN_KEY_TAB             ::Sennet::Key::Tab
#define SN_KEY_BACKSPACE       ::Sennet::Key::Backspace
#define SN_KEY_INSERT          ::Sennet::Key::Insert
#define SN_KEY_DELETE          ::Sennet::Key::Del
#define SN_KEY_RIGHT           ::Sennet::Key::Right
#define SN_KEY_LEFT            ::Sennet::Key::Left
#define SN_KEY_DOWN            ::Sennet::Key::Down
#define SN_KEY_UP              ::Sennet::Key::Up
#define SN_KEY_PAGE_UP         ::Sennet::Key::PageUp
#define SN_KEY_PAGE_DOWN       ::Sennet::Key::PageDown
#define SN_KEY_HOME            ::Sennet::Key::Home
#define SN_KEY_END             ::Sennet::Key::End
#define SN_KEY_CAPS_LOCK       ::Sennet::Key::CapsLock
#define SN_KEY_SCROLL_LOCK     ::Sennet::Key::ScrollLock
#define SN_KEY_NUM_LOCK        ::Sennet::Key::NumLock
#define SN_KEY_PRINT_SCREEN    ::Sennet::Key::PrintScreen
#define SN_KEY_PAUSE           ::Sennet::Key::Pause
#define SN_KEY_F1              ::Sennet::Key::F1
#define SN_KEY_F2              ::Sennet::Key::F2
#define SN_KEY_F3              ::Sennet::Key::F3
#define SN_KEY_F4              ::Sennet::Key::F4
#define SN_KEY_F5              ::Sennet::Key::F5
#define SN_KEY_F6              ::Sennet::Key::F6
#define SN_KEY_F7              ::Sennet::Key::F7
#define SN_KEY_F8              ::Sennet::Key::F8
#define SN_KEY_F9              ::Sennet::Key::F9
#define SN_KEY_F10             ::Sennet::Key::F10
#define SN_KEY_F11             ::Sennet::Key::F11
#define SN_KEY_F12             ::Sennet::Key::F12
#define SN_KEY_F13             ::Sennet::Key::F13
#define SN_KEY_F14             ::Sennet::Key::F14
#define SN_KEY_F15             ::Sennet::Key::F15
#define SN_KEY_F16             ::Sennet::Key::F16
#define SN_KEY_F17             ::Sennet::Key::F17
#define SN_KEY_F18             ::Sennet::Key::F18
#define SN_KEY_F19             ::Sennet::Key::F19
#define SN_KEY_F20             ::Sennet::Key::F20
#define SN_KEY_F21             ::Sennet::Key::F21
#define SN_KEY_F22             ::Sennet::Key::F22
#define SN_KEY_F23             ::Sennet::Key::F23
#define SN_KEY_F24             ::Sennet::Key::F24
#define SN_KEY_F25             ::Sennet::Key::F25

/* keypad */
#define SN_KEY_KP_0            ::Sennet::Key::KP0
#define SN_KEY_KP_1            ::Sennet::Key::KP1
#define SN_KEY_KP_2            ::Sennet::Key::KP2
#define SN_KEY_KP_3            ::Sennet::Key::KP3
#define SN_KEY_KP_4            ::Sennet::Key::KP4
#define SN_KEY_KP_5            ::Sennet::Key::KP5
#define SN_KEY_KP_6            ::Sennet::Key::KP6
#define SN_KEY_KP_7            ::Sennet::Key::KP7
#define SN_KEY_KP_8            ::Sennet::Key::KP8
#define SN_KEY_KP_9            ::Sennet::Key::KP9
#define SN_KEY_KP_DECIMAL      ::Sennet::Key::KPDecimal
#define SN_KEY_KP_DIVIDE       ::Sennet::Key::KPDivide
#define SN_KEY_KP_MULTIPLY     ::Sennet::Key::KPMultiply
#define SN_KEY_KP_SUBTRACT     ::Sennet::Key::KPSubtract
#define SN_KEY_KP_ADD          ::Sennet::Key::KPAdd
#define SN_KEY_KP_ENTER        ::Sennet::Key::KPEnter
#define SN_KEY_KP_EQUAL        ::Sennet::Key::KPEqual

#define SN_KEY_LEFT_SHIFT      ::Sennet::Key::LeftShift
#define SN_KEY_LEFT_CONTROL    ::Sennet::Key::LeftControl
#define SN_KEY_LEFT_ALT        ::Sennet::Key::LeftAlt
#define SN_KEY_LEFT_SUPER      ::Sennet::Key::LeftSuper
#define SN_KEY_RIGHT_SHIFT     ::Sennet::Key::RightShift
#define SN_KEY_RIGHT_CONTROL   ::Sennet::Key::RightControl
#define SN_KEY_RIGHT_ALT       ::Sennet::Key::RightAlt
#define SN_KEY_RIGHT_SUPER     ::Sennet::Key::RightSuper
#define SN_KEY_MENU            ::Sennet::Key::menu

#pragma once

namespace sennet
{

typedef enum class key_code : uint16_t
{
	space               = 32,
	apostrophe          = 39, /* ' */
	comma               = 44, /* , */
	minus               = 45, /* - */
	period              = 46, /* . */
	slash               = 47, /* / */

	d0                  = 48, /* 0 */
	d1                  = 49, /* 1 */
	d2                  = 50, /* 2 */
	d3                  = 51, /* 3 */
	d4                  = 52, /* 4 */
	d5                  = 53, /* 5 */
	d6                  = 54, /* 6 */
	d7                  = 55, /* 7 */
	d8                  = 56, /* 8 */
	d9                  = 57, /* 9 */

	semicolon           = 59, /* ; */
	equal               = 61, /* = */

	a                   = 65,
	b                   = 66,
	c                   = 67,
	d                   = 68,
	e                   = 69,
	f                   = 70,
	g                   = 71,
	h                   = 72,
	i                   = 73,
	j                   = 74,
	k                   = 75,
	l                   = 76,
	m                   = 77,
	n                   = 78,
	o                   = 79,
	p                   = 80,
	q                   = 81,
	r                   = 82,
	s                   = 83,
	t                   = 84,
	u                   = 85,
	v                   = 86,
	w                   = 87,
	x                   = 88,
	y                   = 89,
	z                   = 90,

	left_bracket        = 91,  /* [ */
	backslash	    = 92,  /* \ */
	right_bracket 	    = 93,  /* ] */
	grave_accent        = 96,  /* ` */

	world1              = 161, /* non-US #1 */
	world2              = 162, /* non-US #2 */

	/* Function keys */
	escape              = 256,
	enter               = 257,
	tab                 = 258,
	backspace           = 259,
	insert              = 260,
	del                 = 261,
	right               = 262,
	left                = 263,
	down                = 264,
	up                  = 265,
	page_up             = 266,
	page_down           = 267,
	home                = 268,
	end                 = 269,
	caps_lock           = 280,
	scroll_lock         = 281,
	num_lock            = 282,
	print_screen        = 283,
	pause               = 284,
	f1                  = 290,
	f2                  = 291,
	f3                  = 292,
	f4                  = 293,
	f5                  = 294,
	f6                  = 295,
	f7                  = 296,
	f8                  = 297,
	f9                  = 298,
	f10                 = 299,
	f11                 = 300,
	f12                 = 301,
	f13                 = 302,
	f14                 = 303,
	f15                 = 304,
	f16                 = 305,
	f17                 = 306,
	f18                 = 307,
	f19                 = 308,
	f20                 = 309,
	f21                 = 310,
	f22                 = 311,
	f23                 = 312,
	f24                 = 313,
	f25                 = 314,

	/* keypad */
	kp_0                = 320,
	kp_1                = 321,
	kp_2                = 322,
	kp_3                = 323,
	kp_4                = 324,
	kp_5                = 325,
	kp_6                = 326,
	kp_7                = 327,
	kp_8                = 328,
	kp_9                = 329,
	kp_decimal          = 330,
	kp_divide           = 331,
	kp_multiply         = 332,
	kp_subtract         = 333,
	kp_add              = 334,
	kp_enter            = 335,
	kp_equal            = 336,

	left_shift          = 340,
	left_control        = 341,
	left_alt            = 342,
	left_super          = 343,
	right_shift         = 344,
	right_control       = 345,
	right_alt           = 346,
	right_super         = 347,
	menu                = 348
} key;

inline std::ostream& operator<<(std::ostream& os, key_code kc)
{
	return os << static_cast<int32_t>(kc);
}

}

// From glfw3.h
#define SN_KEY_SPACE           ::sennet::key::space
#define SN_KEY_APOSTROPHE      ::sennet::key::apostrophe    /* ' */
#define SN_KEY_COMMA           ::sennet::key::comma         /* , */
#define SN_KEY_MINUS           ::sennet::key::minus         /* - */
#define SN_KEY_PERIOD          ::sennet::key::period        /* . */
#define SN_KEY_SLASH           ::sennet::key::slash         /* / */
#define SN_KEY_0               ::sennet::key::d0
#define SN_KEY_1               ::sennet::key::d1
#define SN_KEY_2               ::sennet::key::d2
#define SN_KEY_3               ::sennet::key::d3
#define SN_KEY_4               ::sennet::key::d4
#define SN_KEY_5               ::sennet::key::d5
#define SN_KEY_6               ::sennet::key::d6
#define SN_KEY_7               ::sennet::key::d7
#define SN_KEY_8               ::sennet::key::d8
#define SN_KEY_9               ::sennet::key::d9
#define SN_KEY_SEMICOLON       ::sennet::key::semicolon     /* ; */
#define SN_KEY_EQUAL           ::sennet::key::equal         /* = */
#define SN_KEY_A               ::sennet::key::a
#define SN_KEY_B               ::sennet::key::b
#define SN_KEY_C               ::sennet::key::c
#define SN_KEY_D               ::sennet::key::d
#define SN_KEY_E               ::sennet::key::e
#define SN_KEY_F               ::sennet::key::f
#define SN_KEY_G               ::sennet::key::g
#define SN_KEY_H               ::sennet::key::h
#define SN_KEY_I               ::sennet::key::i
#define SN_KEY_J               ::sennet::key::j
#define SN_KEY_K               ::sennet::key::k
#define SN_KEY_L               ::sennet::key::l
#define SN_KEY_M               ::sennet::key::m
#define SN_KEY_N               ::sennet::key::n
#define SN_KEY_O               ::sennet::key::o
#define SN_KEY_P               ::sennet::key::p
#define SN_KEY_Q               ::sennet::key::q
#define SN_KEY_R               ::sennet::key::r
#define SN_KEY_S               ::sennet::key::s
#define SN_KEY_T               ::sennet::key::t
#define SN_KEY_U               ::sennet::key::u
#define SN_KEY_V               ::sennet::key::v
#define SN_KEY_W               ::sennet::key::w
#define SN_KEY_X               ::sennet::key::x
#define SN_KEY_Y               ::sennet::key::y
#define SN_KEY_Z               ::sennet::key::z
#define SN_KEY_LEFT_BRACKET    ::sennet::key::left_bracket   /* [ */
#define SN_KEY_BACKSLASH       ::sennet::key::backslash     /* \ */
#define SN_KEY_RIGHT_BRACKET   ::sennet::key::right_bracket  /* ] */
#define SN_KEY_GRAVE_ACCENT    ::sennet::key::grave_accent   /* ` */
#define SN_KEY_WORLD_1         ::sennet::key::world1        /* non-US #1 */
#define SN_KEY_WORLD_2         ::sennet::key::world2        /* non-US #2 */

/* Function keys */
#define SN_KEY_ESCAPE          ::sennet::key::escape
#define SN_KEY_ENTER           ::sennet::key::enter
#define SN_KEY_TAB             ::sennet::key::tab
#define SN_KEY_BACKSPACE       ::sennet::key::backspace
#define SN_KEY_INSERT          ::sennet::key::insert
#define SN_KEY_DELETE          ::sennet::key::del
#define SN_KEY_RIGHT           ::sennet::key::right
#define SN_KEY_LEFT            ::sennet::key::left
#define SN_KEY_DOWN            ::sennet::key::down
#define SN_KEY_UP              ::sennet::key::up
#define SN_KEY_PAGE_UP         ::sennet::key::page_up
#define SN_KEY_PAGE_DOWN       ::sennet::key::page_down
#define SN_KEY_HOME            ::sennet::key::home
#define SN_KEY_END             ::sennet::key::end
#define SN_KEY_CAPS_LOCK       ::sennet::key::caps_lock
#define SN_KEY_SCROLL_LOCK     ::sennet::key::scroll_lock
#define SN_KEY_NUM_LOCK        ::sennet::key::num_lock
#define SN_KEY_PRINT_SCREEN    ::sennet::key::print_screen
#define SN_KEY_PAUSE           ::sennet::key::pause
#define SN_KEY_F1              ::sennet::key::f1
#define SN_KEY_F2              ::sennet::key::f2
#define SN_KEY_F3              ::sennet::key::f3
#define SN_KEY_F4              ::sennet::key::f4
#define SN_KEY_F5              ::sennet::key::f5
#define SN_KEY_F6              ::sennet::key::f6
#define SN_KEY_F7              ::sennet::key::f7
#define SN_KEY_F8              ::sennet::key::f8
#define SN_KEY_F9              ::sennet::key::f9
#define SN_KEY_F10             ::sennet::key::f10
#define SN_KEY_F11             ::sennet::key::f11
#define SN_KEY_F12             ::sennet::key::f12
#define SN_KEY_F13             ::sennet::key::f13
#define SN_KEY_F14             ::sennet::key::f14
#define SN_KEY_F15             ::sennet::key::f15
#define SN_KEY_F16             ::sennet::key::f16
#define SN_KEY_F17             ::sennet::key::f17
#define SN_KEY_F18             ::sennet::key::f18
#define SN_KEY_F19             ::sennet::key::f19
#define SN_KEY_F20             ::sennet::key::f20
#define SN_KEY_F21             ::sennet::key::f21
#define SN_KEY_F22             ::sennet::key::f22
#define SN_KEY_F23             ::sennet::key::f23
#define SN_KEY_F24             ::sennet::key::f24
#define SN_KEY_F25             ::sennet::key::f25

/* keypad */
#define SN_KEY_KP_0            ::sennet::key::kp_0
#define SN_KEY_KP_1            ::sennet::key::kp_1
#define SN_KEY_KP_2            ::sennet::key::kp_2
#define SN_KEY_KP_3            ::sennet::key::kp_3
#define SN_KEY_KP_4            ::sennet::key::kp_4
#define SN_KEY_KP_5            ::sennet::key::kp_5
#define SN_KEY_KP_6            ::sennet::key::kp_6
#define SN_KEY_KP_7            ::sennet::key::kp_7
#define SN_KEY_KP_8            ::sennet::key::kp_8
#define SN_KEY_KP_9            ::sennet::key::kp_9
#define SN_KEY_KP_DECIMAL      ::sennet::key::kp_decimal
#define SN_KEY_KP_DIVIDE       ::sennet::key::kp_divide
#define SN_KEY_KP_MULTIPLY     ::sennet::key::kp_multiply
#define SN_KEY_KP_SUBTRACT     ::sennet::key::kp_subtract
#define SN_KEY_KP_ADD          ::sennet::key::kp_add
#define SN_KEY_KP_ENTER        ::sennet::key::kp_enter
#define SN_KEY_KP_EQUAL        ::sennet::key::kp_equal

#define SN_KEY_LEFT_SHIFT      ::sennet::key::left_shift
#define SN_KEY_LEFT_CONTROL    ::sennet::key::left_control
#define SN_KEY_LEFT_ALT        ::sennet::key::left_alt
#define SN_KEY_LEFT_SUPER      ::sennet::key::left_super
#define SN_KEY_RIGHT_SHIFT     ::sennet::key::right_shift
#define SN_KEY_RIGHT_CONTROL   ::sennet::key::right_control
#define SN_KEY_RIGHT_ALT       ::sennet::key::right_alt
#define SN_KEY_RIGHT_SUPER     ::sennet::key::right_super
#define SN_KEY_MENU            ::sennet::key::menu

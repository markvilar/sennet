#pragma once

// TODO: Move definitions to build system.
#define SN_DEBUG
#define SN_ENABLE_ASSERTS
#define GLFW_INCLUDE_NONE

#include <memory>

#ifdef __WIN32
	#ifdef __WIN64
		#define SN_PLATFORM_WINDOWS
	#else
		#error "x86 builds not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
	#elif TARGET_OS_IPHONE == 1
		#define SN_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define SN_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__linux__)
	#define SN_PLATFORM_LINUX
#else
	#error "Unknown platform!"
#endif

#ifdef SN_DEBUG
	#if defined(SN_PLATFORM_WINDOWS)
		#define SN_DEBUGBREAK() __debugbreak()
	#elif defined(SN_PLATFORM_LINUX)
		#include <signal.h>
		#define SN_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define SN_ENABLE_ASSERTS
#else
	#define SN_DEBUGBREAK()
#endif

// TODO: Make macro able to take in no arguments except condition.
#ifdef SN_ENABLE_ASSERTS							
	#define SN_ASSERT(x, ...)						\
	{ 									\
		if(!(x)) 							\
		{								\
			SN_ERROR("Assertion failed: {0}", __VA_ARGS__);		\
			SN_DEBUGBREAK();					\
		} 								\
	}
	#define SN_CORE_ASSERT(x, ...)						\
	{ 									\
		if(!(x)) 							\
		{								\
			SN_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__);	\
			SN_DEBUGBREAK();					\
		} 								\
	}
#else
	#define SN_ASSERT(x, ...)
	#define SN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Sennet
{

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

}

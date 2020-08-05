#include <sennet/pch.hpp>

#include <sennet/core/window.hpp>

#if defined(SN_PLATFORM_WINDOWS)
	#include <sennet/platform/windows/windows_window.hpp>
#elif defined(SN_PLATFORM_LINUX)
	#include <sennet/platform/linux/linux_window.hpp>
#endif

namespace sennet
{

scope<window> window::create(const window_props& props)
{
#if defined(SN_PLATFORM_WINDOWS)
	return create_scope<windows_window>(props);
#elif defined(SN_PLATFORM_LINUX)
	return create_scope<linux_window>(props);
#else
	SN_CORE_ASSERT(false, "Unsupported platform!");
	return nullptr;
#endif
}

}

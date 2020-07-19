#include <sennet/snpch.hpp>

#include <sennet/core/window.hpp>

#ifdef SN_PLATFORM_WINDOWS
	#include <sennet/platform/windows_window.hpp>
#endif

namespace sennet
{

scope<window> window::create(const window_props& props)
{
#ifdef SN_PLATFORM_WINDOWS
	return create_scope<windows_window>(props);
#else
	SN_CORE_ASSERT(false, "Unsupported platform!");
	return nullptr;
#endif
}

}

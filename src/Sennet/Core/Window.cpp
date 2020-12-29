#include "Sennet/Pch.hpp"
#include "Sennet/Core/Window.hpp"

#if defined(SN_PLATFORM_WINDOWS)
	#include "Platform/Windows/WindowsWindow.hpp"
#elif defined(SN_PLATFORM_LINUX)
	#include "Platform/Linux/LinuxWindow.hpp"
#endif

namespace Sennet
{

Scope<Window> Window::Create(const WindowProperties& props)
{
#if defined(SN_PLATFORM_WINDOWS)
	return CreateScope<WindowsWindow>(props);
#elif defined(SN_PLATFORM_LINUX)
	return CreateScope<LinuxWindow>(props);
#else
	SN_CORE_ASSERT(false, "Unsupported platform!");
	return nullptr;
#endif
}

}

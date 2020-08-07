#pragma once

#include <algorithm>
#include <iosfwd>
#include <iostream>
#include <stdexcept>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>
#include <sstream>
#include <string>
#include <thread>
#include <queue>

#include <Sennet/Core/Log.hpp>

#ifdef SN_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

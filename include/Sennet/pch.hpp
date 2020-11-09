#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iosfwd>
#include <iostream>
#include <stdexcept>

#include <array>
#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <thread>
#include <queue>

#include "Sennet/Core/Log.hpp"
#include "Sennet/Debug/Instrumentor.hpp"

#ifdef SN_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

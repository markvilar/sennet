#pragma once

#include <algorithm>
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

#include <sennet/core/log.hpp>

#ifdef SN_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

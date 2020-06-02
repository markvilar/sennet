#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include <zedutils/am/core.hpp>

namespace am {

class log
{
public: 
	static void init(const std::string name);

	inline static std::shared_ptr<spdlog::logger>& get_logger() 
	{ 
		return m_logger;
	}

private:
	static std::shared_ptr<spdlog::logger> m_logger;
};

};

// Log macros.
#define AM_ERROR(...)    ::am::log::get_logger()->error(__VA_ARGS__)
#define AM_WARN(...)     ::am::log::get_logger()->warn(__VA_ARGS__)
#define AM_INFO(...)     ::am::log::get_logger()->info(__VA_ARGS__)
#define AM_TRACE(...)    ::am::log::get_logger()->trace(__VA_ARGS__)
#define AM_FATAL(...)    ::am::log::get_logger()->fatal(__VA_ARGS__)

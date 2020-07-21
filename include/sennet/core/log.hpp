#pragma once

#include <sennet/core/base.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace sennet 
{

class log
{
public: 
	static void init();

	static ref<spdlog::logger>& get_core_logger() 
	{
		return s_core_logger;
	}
	
	static ref<spdlog::logger>& get_client_logger() 
	{
		return s_client_logger;
	}

private:
	static ref<spdlog::logger> s_core_logger;
	static ref<spdlog::logger> s_client_logger;
};

}

// Core log macros.
#define SN_CORE_TRACE(...) \
	::sennet::log::get_core_logger()->trace(__VA_ARGS__)
#define SN_CORE_INFO(...) \
	::sennet::log::get_core_logger()->info(__VA_ARGS__)
#define SN_CORE_WARN(...) \
	::sennet::log::get_core_logger()->warn(__VA_ARGS__)
#define SN_CORE_ERROR(...) \
	::sennet::log::get_core_logger()->error(__VA_ARGS__)
#define SN_CORE_CRITICAL(...) \
	::sennet::log::get_core_logger()->critical(__VA_ARGS__)

// Client log macros.
#define SN_TRACE(...) \
	::sennet::log::get_client_logger()->trace(__VA_ARGS__)
#define SN_INFO(...) \
	::sennet::log::get_client_logger()->info(__VA_ARGS__)
#define SN_WARN(...) \
	::sennet::log::get_client_logger()->warn(__VA_ARGS__)
#define SN_ERROR(...) \
	::sennet::log::get_client_logger()->error(__VA_ARGS__)
#define SN_CRITICAL(...) \
	::sennet::log::get_client_logger()->critical(__VA_ARGS__)

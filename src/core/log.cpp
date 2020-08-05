#include <sennet/pch.hpp>
#include <sennet/core/log.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace sennet 
{

ref<spdlog::logger> log::s_core_logger;
ref<spdlog::logger> log::s_client_logger;

void log::init()
{
	std::vector<spdlog::sink_ptr> sinks;
	sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
		"sennet.log", true));
		
	sinks[0]->set_pattern("%^[%T] %n: %v%$");
	sinks[1]->set_pattern("[%T] [%l] %n: %v");

	// Core logger.
	s_core_logger = std::make_shared<spdlog::logger>(
		"SENNET", begin(sinks), end(sinks));
	spdlog::register_logger(s_core_logger);
	s_core_logger->set_level(spdlog::level::trace);
	s_core_logger->flush_on(spdlog::level::trace);

	// Client logger.
	s_client_logger = std::make_shared<spdlog::logger>(
		"APP", begin(sinks), end(sinks));
	spdlog::register_logger(s_client_logger);
	s_client_logger->set_level(spdlog::level::trace);
	s_client_logger->flush_on(spdlog::level::trace);
}

}

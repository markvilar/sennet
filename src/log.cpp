#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <sennet/log.hpp>

namespace sennet 
{

log::log(const std::string& name)
{
	// Create console sink.
	auto console_sink = 
		std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::trace);
	console_sink->set_pattern("%^[%T] %n: %v%$");

	// Create logger.
	m_logger.reset(new spdlog::logger(name, console_sink));
	m_logger->set_level(spdlog::level::trace);
}

log::log(const std::string& name, const std::string& file_path)
{
	// Create console sink.
	auto console_sink = 
		std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::trace);
	console_sink->set_pattern("%^[%T] %n: %v%$");

	// Create file sink.
	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
		file_path, true);
	file_sink->set_level(spdlog::level::trace);

	// Create logger.
	m_logger.reset(new spdlog::logger(name, {console_sink, file_sink}));
	m_logger->set_level(spdlog::level::trace);
}

log::~log()
{
}

};

#include <spdlog/sinks/stdout_color_sinks.h>

#include <zedutils/log.hpp>

namespace am {

std::shared_ptr<spdlog::logger> log::m_logger;

void log::init(const std::string name)
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	m_logger = spdlog::stdout_color_mt(name);
	m_logger->set_level(spdlog::level::trace);
}

};

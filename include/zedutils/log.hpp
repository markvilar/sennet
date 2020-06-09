#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include <zedutils/am/core.hpp>

namespace am {

class log
{
public: 
	// Console logger constructor.
	log(const std::string& name);

	// Console and file logger constructor.
	log(const std::string& name, const std::string& file_path);

	// Destructor.
	~log();

	// Returns the underlying spdlog logger.
	inline std::shared_ptr<spdlog::logger>& get_logger() 
	{ 
		return m_logger;
	}

private:
	std::shared_ptr<spdlog::logger> m_logger;
};

};

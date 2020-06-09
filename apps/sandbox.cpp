#include <iostream>
#include <tuple>

#include <boost/asio.hpp>

#include <glad/glad.h>

#include <zedutils/am/actions.hpp>
#include <zedutils/am/core.hpp>
#include <zedutils/log.hpp>

int main()
{
	am::log log("test logger", "logs/test.txt");
	log.get_logger()->error("error");
	log.get_logger()->warn("warn");
	log.get_logger()->info("info");
	log.get_logger()->trace("trace");
	return 0;
}

#include <iostream>
#include <tuple>

#include <boost/asio.hpp>

#include <glad/glad.h>

#include <sl/Camera.hpp>

#include <sennet/am/actions.hpp>
#include <sennet/am/core.hpp>
#include <sennet/log.hpp>
#include <sennet/handlers/zed_recorder.hpp>

int main()
{	
	sennet::log log("test logger", "logs/test.txt");
	log.get_logger()->error("error");
	log.get_logger()->warn("warn");
	log.get_logger()->info("info");
	log.get_logger()->trace("trace");

	sennet::zed_recorder handler;
	std::cout << handler.get_name() << "\n";

	return 0;
}

#include <iostream>
#include <tuple>

#include <boost/asio.hpp>

#include <glad/glad.h>

#include <sl/Camera.hpp>

#include <zedutils/am/actions.hpp>
#include <zedutils/am/core.hpp>
#include <zedutils/log.hpp>

int main()
{	/*
	am::log log("test logger", "logs/test.txt");
	log.get_logger()->error("error");
	log.get_logger()->warn("warn");
	log.get_logger()->info("info");
	log.get_logger()->trace("trace");
	*/

	sl::Camera zed;
	sl::InitParameters init_params;
	init_params.input.setFromSVOFile("remote_recording.svo");
	init_params.camera_disable_self_calib = true;

	auto zed_open_state = zed.open(init_params);
	if(zed_open_state != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << "Open state: " << sl::toString(zed_open_state) << "\n";
		return 1;
	}

	unsigned int i = 0;
	while (zed.grab() == sl::ERROR_CODE::SUCCESS)
	{
		i++;
		std::cout << "Grab #" << i << " succeeded!\n";
	}

	return 0;
}

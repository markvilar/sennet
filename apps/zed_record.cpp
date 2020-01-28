#include <iostream>
#include <iomanip>
#include <string>

#include <sl/Camera.hpp>

#include <zed_utils/zed_utils.hpp>

int main()
{
	// Initialize camera
	sl::Camera zed;

	// Initial parameters
	sl::InitParameters param;
	param.sdk_verbose = true;
	param.camera_resolution = sl::RESOLUTION::HD2K;

	// Open camera
	sl::ERROR_CODE error = zed.open(param);
	if (error != sl::ERROR_CODE::SUCCESS) 
	{
		print("Opening ZED : ", error, "");
		zed.close();
		exit(-1);
	}
	else
	{
		std::cout << "Opened ZED!" << std::endl;
	}

	zed.close();
}

#include <sl/Camera.hpp>

#include <iostream>

int main()
{
	// Initialize camera
	sl::Camera zed;

	// Configuration parameters
	sl::InitParameters init_params;
	init_params.sdk_verbose = true;

	// Open camera
	sl::ERROR_CODE err = zed.open(init_params);
	if (err != sl::SUCCESS)
	{
		std::cout << "Couldn't open ZED camera..." << std::endl;
		exit(-1);
	}

	// Close camera
	zed.close();

	std::cout << "ZED application executed!" << std::endl;
	return 0;
}

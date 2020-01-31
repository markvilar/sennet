#include <zedutils/ZEDio.hpp>
#include <zedutils/ZEDController.hpp>

#include <sl/Camera.hpp>

#include <iostream>
#include <iomanip>
#include <string>

int main()
{
	// Camera
	sl::Camera zed;


	// Initial camera parameters
	sl::InitParameters init_params;
	std::cout << init_params << std::endl;
	init_params.camera_resolution = sl::RESOLUTION::HD1080;
	init_params.camera_fps = 30;
	init_params.camera_disable_self_calib = true;
	init_params.enable_right_side_measure = false;
	init_params.svo_real_time_mode = false;
	init_params.depth_mode = sl::DEPTH_MODE::NONE;
	init_params.sdk_verbose = true;
	init_params.sensors_required = true;
	init_params.enable_image_enhancement = true;
	std::cout << init_params << std::endl;


	// Runtime parameters
	sl::RuntimeParameters run_params;
	std::cout << run_params << std::endl;
	run_params.sensing_mode = sl::SENSING_MODE::STANDARD;
	run_params.measure3D_reference_frame = sl::REFERENCE_FRAME::CAMERA;
	run_params.enable_depth = false;
	run_params.confidence_threshold = 50;
	run_params.textureness_confidence_threshold = 50;
	std::cout << run_params << std::endl;


	// Controller
	ZEDController controller;

	// Bind camera
	controller.bind_camera(&zed);

	// Open camera
	sl::ERROR_CODE error = controller.open_camera(init_params);
	if (error != sl::ERROR_CODE::SUCCESS)
	{
		print("", error, "");
		exit(-1);
	}

	std::cout << controller << std::endl;

	// Recording parameters
	sl::RecordingParameters rec_params = sl::RecordingParameters(
			"/home/martin/Downloads/zed/test.svo",
			sl::SVO_COMPRESSION_MODE::H264);
	
	// Enable recording
	error = zed.enableRecording(rec_params);
			
	int i = 0;
	int n_frames = 500;
	while (i < n_frames)
	{
		if (zed.grab() == sl::ERROR_CODE::SUCCESS)
		{
			i++;
			std::cout << "Grabbed frame " << i << "/" << n_frames
				<< std::endl;
		}
	}

	zed.disableRecording();
	controller.close_camera();
	return 0;
}

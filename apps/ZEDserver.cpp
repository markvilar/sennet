#include <ZEDutils/ZEDio.hpp>
#include <ZEDutils/ZEDController.hpp>

#include <boost/asio.hpp>

#include <sl/Camera.hpp>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	// Camera
	sl::Camera zed;
	
	// Initial camera parameters
	sl::InitParameters init_params;
	init_params.camera_resolution = sl::RESOLUTION::HD720;
	init_params.camera_fps = 30;
	init_params.camera_disable_self_calib = false;
	init_params.enable_right_side_measure = false;
	init_params.svo_real_time_mode = false;
	init_params.depth_mode = sl::DEPTH_MODE::ULTRA; // Disable depth
	init_params.sdk_verbose = true;
	init_params.sensors_required = true; // Require IMU
	init_params.enable_image_enhancement = true;
	
	// Runtime parameters
	sl::RuntimeParameters run_params;
	run_params.sensing_mode = sl::SENSING_MODE::STANDARD; // Depth sensing
	run_params.measure3D_reference_frame = sl::REFERENCE_FRAME::CAMERA;
	run_params.enable_depth = false;
	run_params.confidence_threshold = 80;
	run_params.textureness_confidence_threshold = 80;
	
	// Controller
	std::string output_path = "~/dev/zedutils/data/cblock";
	ZEDController controller(output_path);


	// Bind camera
	controller.bind_camera(&zed);
	
	
	// Open camera
	sl::ERROR_CODE open_error = controller.open_camera(init_params);
	if (open_error != sl::ERROR_CODE::SUCCESS)
	{
		print("", open_error, "");
		exit(-1);
	}
	
	// Recording parameters
	sl::String file_path = "/home/martin/dev/zedutils/data/cblock/recording.svo";
	auto compression_mode = sl::SVO_COMPRESSION_MODE::H264; // Req. NVIDIA GPU
	sl::RecordingParameters rec_params = sl::RecordingParameters(
			file_path, compression_mode);
			
	
	// Enable recording
	auto rec_error = controller.enable_camera_recording(rec_params);
	if (rec_error != sl::ERROR_CODE::SUCCESS)
	{
		print("", rec_error, "");
		exit(-1);
	}


	// Record
	rec_error = controller.camera_record(run_params, 90);
	if (rec_error != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << "Could not record!" << std::endl;
		print("", rec_error, "");
		exit(-1);
	}
	controller.disable_camera_recording();
	
	
	// Close
	controller.close_camera();
	return 0;
}

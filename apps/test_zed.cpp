#include <iostream>

#include <sl/Camera.hpp>

#include <zedutils/active_messaging/zed.hpp>

int main(int argc, char* argv[])
{
	// Initialization camera
	std::shared_ptr<sl::Camera> cam(new sl::Camera);
	sl::InitParameters init_params;
	init_params.sdk_verbose = true;
	init_params.camera_resolution = sl::RESOLUTION::HD1080;
	init_params.camera_fps = 30;
	init_params.depth_mode = sl::DEPTH_MODE::NONE;

	// Recording parameters
	sl::RecordingParameters rec_params;
	rec_params.video_filename = "../../data/test.svo";
	rec_params.compression_mode = sl::SVO_COMPRESSION_MODE::H264;

	std::string port = "8000";
	std::string root = "/home/martin/dev/zedutils/data/am_test/";

	zed::am::zed_runtime rt(port, root);
	return 0;
};

#include <sl/Camera.hpp>
#include <zedutils/active_messaging/core.hpp>

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

	// Open camera
	auto error = cam->open(init_params);
	if (error != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << "Could not open camera..." << std::endl;
	}

	// Enable recording
	error = cam->enableRecording(rec_params);
	if (error != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << "Could not enable recording..." << std::endl;
	}

	// Retrieve image from camera
	sl::Mat image;
	cam->retrieveImage(image, sl::VIEW::LEFT, sl::MEM::CPU);
	std::cout << "Image: " 
		<< "\n- width: " << image.getWidth()
		<< "\n- height: " << image.getHeight()
		<< "\n- channels: " << image.getChannels()
		<< "\n- type: " << image.getDataType() 
		<< "\n- pixel bytes: " << image.getPixelBytes();

	// Convert image to sendable format

	// Send image over socket

	// Close camera
	cam->close();

	return 0;
};

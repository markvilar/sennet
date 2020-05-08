#include <zedutils/network.hpp>

#include <sl/Camera.hpp>

#include <chrono>
#include <iostream>
#include <thread>

const unsigned int DEFAULT_THREAD_POOL_SIZE = 2;

int main(int argc, char* argv[])
{
	// Application options
	bool log_file = false;
	
	// Application settings
	unsigned short port = 3333;
	// Twice the number of processors
	unsigned int thread_pool_size = std::thread::hardware_concurrency() * 2;
	auto log_file_path = sl::String("../../data/log.txt");
	auto svo_file_path = sl::String("../../data/test.svo");

	boost::shared_ptr<sl::Camera> cam(new sl::Camera);

	// Initialization parameters
	sl::InitParameters init_params;
	init_params.sdk_verbose = true;
	init_params.camera_resolution = sl::RESOLUTION::HD1080;
	init_params.camera_fps = 30;
	init_params.depth_mode = sl::DEPTH_MODE::NONE;
	if (log_file)
	{
		init_params.sdk_verbose_log_file = sl::String(log_file_path);
	}

	// Recording parameters
	sl::RecordingParameters rec_params;
	rec_params.video_filename = svo_file_path;
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

	// Run server
	try
	{
		unsigned int frame_count = 0;
		unsigned int total_count = 1000;
		zed::net::Server srv;
		
		if (thread_pool_size == 0)
			thread_pool_size = DEFAULT_THREAD_POOL_SIZE;
		
		srv.start(port, thread_pool_size);

		while (frame_count < total_count)
		{
			error = cam->grab();
			if (error != sl::ERROR_CODE::SUCCESS)
			{
				std::cout << "Error when grabbing frame..." 
					<< std::endl;
			}
			else
			{
				frame_count++;
				std::cout << "Grabbed frame successfully!" 
					<< std::endl;
			}
			
			// Sleep thread
			std::this_thread::sleep_for(std::chrono::milliseconds(
				10));
		}
		
		srv.stop();
	}
	catch (boost::system::system_error& b_ec)
	{
		// Catch boost error
		std::cout << "[" << std::this_thread::get_id()
			<< "][" << __FUNCTION__ << "] Error code: " << b_ec.code()
			<< ". Message: " << b_ec.what() << std::endl;
	}
	catch (sl::ERROR_CODE sl_ec)
	{
		// Catch stereolabs error
		std::cout << sl::toString(sl_ec) << std::endl;
	}

	// Close camera
	cam->close();

	return 0;
}

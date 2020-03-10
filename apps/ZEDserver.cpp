#include <ZEDutils/ZEDio.hpp>
#include <ZEDutils/ZEDnetwork.hpp>
#include <ZEDutils/ZEDtypes.hpp>

#include <boostnet/network.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <sl/Camera.hpp>

#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <typeinfo>

int main(int argc, char* argv[])
{
	// Initialize mutex, camera and hive
	//boost::shared_ptr<boost::mutex> mutex_ptr(new boost::mutex());
	sl::Camera* cam = new sl::Camera();
	boost::shared_ptr<Hive> hive(new Hive(boost::shared_ptr<boost::mutex> (
		new boost::mutex())));

	
	// Open camera
	sl::InitParameters init_params;
	init_params.sdk_verbose = true;
	init_params.camera_fps = 30;
	init_params.camera_resolution = sl::RESOLUTION::HD2K;
	auto error = cam->open(init_params);
	if(error != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << "[ERROR] " << sl::toVerbose(error) << std::endl;
	}
	
		
	// Enable recording
	sl::String rec_file = "/home/martin/dev/zedutils/data/server_test.svo";
	auto rec_compress = sl::SVO_COMPRESSION_MODE::H264;
	auto rec_params = sl::RecordingParameters(rec_file, rec_compress);
	error = cam->enableRecording(rec_params);
	if(error != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << "[ERROR] " << sl::toVerbose(error) << std::endl;
	}

	
	// Set up image connections
	boost::shared_ptr<ImageConnection> left_img_conn(new ImageConnection(
		hive));
	boost::shared_ptr<ImageConnection> right_img_conn(new ImageConnection(
		hive));
	left_img_conn->Bind("127.0.0.1", 10000);
	right_img_conn->Bind("127.0.0.1", 11000);

	
	// Initialize images and byte vectors
	sl::Mat left_image, right_image;
	std::vector<boost::uint8_t> left_bytes, right_bytes;
	
	
	// Record loop
	unsigned int frame_count = 0;
	unsigned int total_frames = 120;
	unsigned int send_every = 10;
	sl::uchar4 val;
	try
	{
		while(frame_count < total_frames) // While no interrupt or quit
		{
			error = cam->grab();
			if(error == sl::ERROR_CODE::SUCCESS)
			{
				++frame_count;
				std::cout << "Frames: " << frame_count << "/"
					<< total_frames << std::endl;
								
				// Collect threads
				hive->Poll();
				
				// Retrieve images
				cam->retrieveImage(left_image, sl::VIEW::LEFT);
				cam->retrieveImage(right_image, sl::VIEW::RIGHT);
				
				// Create byte vectors
				left_bytes = slMat2Vec(left_image);
				right_bytes = slMat2Vec(right_image);
				
				// Sleep
				boost::this_thread::sleep(
					boost::posix_time::milliseconds(1));
			}
			else
			{
				std::cout << "[ERROR] " << sl::toVerbose(error) 
					<< std::endl;
			}
		}
	}
	catch(std::exception& ex)
	{
		std::cout << "[EXCEPTION]: " << ex.what() << std::endl;
	}
	
	
	// Stop hive
	hive->Stop();
	
	
	// Close and deallocate camera
	cam->close();
	delete cam;
	
	return 0;
}

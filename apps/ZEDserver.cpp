#include <ZEDutils/ZEDio.hpp>
#include <ZEDutils/ZEDnetwork.hpp>

#include <boostnet/network.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <sl/Camera.hpp>

int main(int argc, char* argv[])
{
	// Initialize mutex, camera and hive
	boost::shared_ptr<boost::mutex> mutex_ptr(new boost::mutex());
	sl::Camera* cam = new sl::Camera();
	boost::shared_ptr<Hive> hive(new Hive(mutex_ptr));

	
	// Open camera
	sl::InitParameters init_params;
	init_params.sdk_verbose = true;
	init_params.camera_fps = 30;
	init_params.camera_resolution = sl::RESOLUTION::HD720;
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

	
	// Set up connection
	boost::shared_ptr<CameraConnection> connection(new CameraConnection(
		hive, cam));
	// connection->SetReceiveBufferSize(); // Set tcp receive buffer size
	connection->SetTimerInterval(2000); // 2 second timer

	
	// Set up acceptor
	boost::shared_ptr<CameraAcceptor> acceptor(new CameraAcceptor(hive));
	acceptor->Listen("127.0.0.1", 7777);
	acceptor->Accept(connection);
	

	// Record loop
	unsigned int frame_count = 0;
	unsigned int total_frames = 10;
	unsigned int send_every = 10;
	sl::Mat left_image, right_image;
	try
	{
		while(frame_count < total_frames)
		{
			error = cam->grab();
			if(error == sl::ERROR_CODE::SUCCESS)
			{
				frame_count++;
				std::cout << "Frame count: " << frame_count 
					<< "/" << total_frames << std::endl;
				
				// Collect threads
				hive->Poll();
				
				// Retrieve images
				cam->retrieveImage(left_image, sl::VIEW::LEFT);
				cam->retrieveImage(right_image, sl::VIEW::RIGHT);

				std::cout << "Left image: " 
					<< left_image.getWidth() << "x"
					<< left_image.getHeight() << "x"
					<< left_image.getChannels() << ", "
					<< left_image.getPixelBytes() << ", "
					<< left_image.getDatatype()
					<< std::endl;

				std::cout << "Right image: " 
					<< right_image.getWidth() << "x"
					<< right_image.getHeight() << "x"
					<< right_image.getChannels() << ", "
					<< right_image.getPixelBytes() 
					<< std::endl;
				
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
		std::cout << "[Exception]: " << ex.what() << std::endl;
	}
	
	
	// Stop hive
	hive->Stop();
	
	
	// Close and deallocate camera
	cam->close();
	delete cam;
	
	return 0;
}

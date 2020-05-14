#include <boost/asio.hpp>

#include <sl/Camera.hpp>

#include <iostream>
#include <memory>
#include <thread>
#include <vector>

int main(int argc, char* argv[])
{
	// Size of the queue containing pending connection requests
	const int BACKLOG_SIZE = 30;
	
	// Step 1: Here we assume that the server application has
	// already obtained the protocol port number.
	unsigned short port_num = 3333;
	
	// Step 2: Creating a server endpoint.
	boost::asio::ip::tcp::endpoint
		ep(boost::asio::ip::address_v4::any(), port_num);

	boost::asio::io_service ios;
	try
	{
		// Step 3: Instantiating and opening an acceptor (passive) socket.
		boost::asio::ip::tcp::acceptor acceptor(ios, ep.protocol());

		// Step 4: Binding the acceptor socket to the server endpoint.
		acceptor.bind(ep);

		// Step 5: Starting to listen for incoming connection requests.
		acceptor.listen(BACKLOG_SIZE);
		std::cout << "[SERVER] Listening on port: " << port_num << "\n";

		// Step 6: Creating an active socket.
		boost::asio::ip::tcp::socket sock(ios);

		// Step 7: Processing the next connection request and connecting
		// the active socket to the client.
		acceptor.accept(sock);

		// At this point 'sock' socket is connected to the client
		// application and can be used to send data to or receive data
		// from it.
	}
	catch (boost::system::system_error& e)
	{
		std::cout << "Error occured! Error code: " << e.code()
			<< ". Message: " << e.what();
	}

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

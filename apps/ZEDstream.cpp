#include <ZEDutils/ZEDio.hpp>

#include <sl/Camera.hpp>

#include <iostream>

static bool exit_app = false;

// Handle the CTRL-C keyboard signal
#ifdef _WIN32
#include <Windows.h>
void CtrlHandler(DWORD fdwCtrlType) {
    exit_app = (fdwCtrlType == CTRL_C_EVENT);
}
#else
#include <signal.h>
void nix_exit_handler(int s) {
    exit_app = true;
}
#endif

// Set the function to handle the CTRL-C
void SetCtrlHandler() {
#ifdef _WIN32 // windows
    SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandler, TRUE);
#else // unix
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = nix_exit_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
#endif
}


int main()
{
	// Camera
	sl::Camera zed;
	
	// Initialization parameters
	sl::InitParameters init_params;
	init_params.camera_resolution = sl::RESOLUTION::HD720;
	init_params.sdk_verbose = true;

	// Open
	auto error = zed.open(init_params);
	if (error != sl::ERROR_CODE::SUCCESS)
	{
		print("Open camera: ", error, "");
	}

	
	// Streaming parameters
	sl::StreamingParameters stream_params;
	stream_params.codec = sl::STREAMING_CODEC::H264;
	stream_params.port = 30000;
	stream_params.bitrate = 10000;

	
	// Enable streaming
	error = zed.enableStreaming(stream_params);
	if (error != sl::ERROR_CODE::SUCCESS)
	{
		print("Enable streaming: ", error, "");
		return 1;
	}

	
	// Stream loop
	while (!exit_app)
	{
		error = zed.grab();
		if (error != sl::ERROR_CODE::SUCCESS)
		{
			print("Grab loop: ", error, "");
		}
		else
		{
			sl::sleep_ms(1);
		}
	}
	
	// Disable streaming and close
	zed.disableStreaming();
	zed.close();
	return 0;
}

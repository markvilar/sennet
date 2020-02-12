#include <sl/Camera.hpp>

#include <ZEDutils/ZEDListener.hpp>
#include <ZEDutils/ZEDStreamer.hpp>
#include <ZEDutils/ZEDio.hpp>


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
	//sl::String ip = "10.22.103.170"; // Private IP BROADCAST (IPv4)
	sl::String ip = "127.0.0.1"; // Private IP LOOPBACK (IPv4)
	unsigned int port = 30000;
	init_params.input.setFromStream(ip, port);
	init_params.sdk_verbose = true;

	// Open
	auto error = zed.open(init_params);
	if (error != sl::ERROR_CODE::SUCCESS)
	{
		print("", error, "");
		zed.close();
		return 1;
	}


	// Capture loop
	sl::Mat left_image;
	sl::Mat right_image;
	while (!exit_app)
	{
		error = zed.grab();
		if (error != sl::ERROR_CODE::SUCCESS)
		{
			print("Error during capture: ", error, "");
			break;
		}
		else
		{
			error = zed.retrieveImage(left_image, sl::VIEW::LEFT);
			error = zed.retrieveImage(right_image, sl::VIEW::RIGHT);
		}
	}

	// Close
	zed.close();
	return 0;
}

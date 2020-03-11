#include <ZEDutils/ZEDnetwork.hpp>
#include <ZEDutils/ZEDtypes.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <sl/Camera.hpp>

#include <iostream>

static bool exit_app = false;

#ifdef _WIN32
#include <Windows.h>
void CtrlHandler(DWORD fdwCtrlType)
{
	exit_app = (fwdCtrlType == CTRL_C_EVENT);
}
#else
#include <signal.h>
void nix_exit_handler(int s)
{
	exit_app = true;
}
#endif

void SetCtrlHandler() 
{
#ifdef _WIN32
	SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandler, TRUE);
#else
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = nix_exit_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
#endif
}

int main(int argc, char* argv[])
{
	boost::shared_ptr<Hive> hive(new Hive(boost::shared_ptr<boost::mutex>(
		new boost::mutex())));

	// Set up image connections
	boost::shared_ptr<ImageConnection> l_conn(new ImageConnection(
			hive));
	boost::shared_ptr<ImageConnection> r_conn(new ImageConnection(
			hive));
	l_conn->Connect("127.0.0.1", 10000);
	r_conn->Connect("127.0.0.1", 11000);
	
	// Set up ctrl handle
	SetCtrlHandler();
	
	while(!exit_app)
	{
		hive->Poll();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	// Stop hive
	hive->Stop();
	
	return 0;
}

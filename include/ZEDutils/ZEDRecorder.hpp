#include <sl/Camera.hpp>

class ZEDRecorder
{
	private:
		sl::String dir;
		sl::Camera* zed;
		sl::InitParameters init_params;
		sl::RuntimeParameters run_params;
		sl::RecordingParameters rec_params;
	public:
		// Misc
		ZEDRecorder();
		~ZEDRecorder();


		// Control


		// Camera control


		// Record
};

#include <ZEDutils/ZEDController.hpp>

ZEDController::ZEDController(const std::string path) 
	: camera(nullptr), dir_path(path)
{
	this->init_params = sl::InitParameters();
	this->run_params = sl::RuntimeParameters();
	this->rec_params = sl::RecordingParameters();
	static unsigned int id = 0;
	id++;
	m_ID = id;
}


ZEDController::~ZEDController()
{
	if(is_camera_opened())
	{
		close_camera();
	}
	unbind_camera();
}


bool ZEDController::is_camera_bounded() const
{
	if (camera == nullptr)
	{
		return false;
	}
	return true;
}


bool ZEDController::is_camera_opened() const
{
	if (is_camera_bounded())
	{
		return camera->isOpened();
	}
	return false;
}


void ZEDController::bind_camera(sl::Camera* camera) 
{
	if (!is_camera_bounded())
	{
		// Assign new camera
		this->camera = camera;
	}
	return;
}


void ZEDController::unbind_camera()
{
	if (is_camera_bounded())
	{
		camera = nullptr;
	}
}


sl::ERROR_CODE ZEDController::open_camera(const sl::InitParameters param) const
{
	// Initialize to failure
	auto error = sl::ERROR_CODE::FAILURE;
	if (is_camera_opened())
	{
		error = sl::ERROR_CODE::SUCCESS;
	}
	else if (is_camera_bounded() && !is_camera_opened())
	{
		error = camera->open(param);
	}
	return error;
}


void ZEDController::close_camera() const
{
	if (is_camera_bounded())
	{
		camera->close();
	}
}


sl::InitParameters ZEDController::get_init_parameters() const
{
	sl::InitParameters params;
	if (is_camera_opened())
	{
		params = camera->getInitParameters();
	}
	return params;
}


sl::RuntimeParameters ZEDController::get_runtime_parameters() const
{
	sl::RuntimeParameters params;
	if (is_camera_opened())
	{
		params = camera->getRuntimeParameters();
	}
	return params;
}


sl::CameraInformation ZEDController::get_camera_info() const
{
	//TODO: Make this function more robust?
	sl::CameraInformation info;
	if (is_camera_opened())
	{
		info = camera->getCameraInformation();
	}
	return info;
}


void ZEDController::set_camera_settings(sl::VIDEO_SETTINGS settings, int value) 
	const
{
	if (is_camera_opened())
	{
		camera->setCameraSettings(settings, value);
	}
}


int ZEDController::get_camera_settings(sl::VIDEO_SETTINGS settings) const
{
	if (is_camera_opened())
	{
		return camera->getCameraSettings(settings);
	}
	else
	{
		return -1;
	}
	
}


float ZEDController::get_camera_fps() const
{
	if (is_camera_opened())
	{
		return camera->getCurrentFPS();
	}
	else
	{
		return 0.0;
	}
}


sl::ERROR_CODE ZEDController::enable_camera_recording(
		sl::RecordingParameters params) const
{
	if (is_camera_opened())
	{
		return camera->enableRecording(params);
	}
	else
	{
		return sl::ERROR_CODE::FAILURE;
	}
}


void ZEDController::disable_camera_recording() const
{
	if (is_camera_opened())
	{
		camera->disableRecording();
	}
}


bool ZEDController::is_camera_recording() const
{
	auto rec_status = get_camera_recording_status();
	return rec_status.is_recording;
}


bool ZEDController::is_camera_paused() const
{
	auto rec_status = get_camera_recording_status();
	return rec_status.is_paused;
}


sl::ERROR_CODE ZEDController::camera_record(sl::RuntimeParameters params,
		unsigned int count) const
{
	// TODO: Implement recording enabled check
	if (!is_camera_opened())
	{
		return sl::ERROR_CODE::FAILURE;
	}
	else
	{
		// Capture frames
		unsigned int frame_count = 0;
		while (frame_count < count)
		{
			if (camera->grab(run_params) == sl::ERROR_CODE::SUCCESS)
			{
				frame_count++;
				std::cout << "Grabbed frame: " << frame_count
					<< "/" << count << std::endl;
			}
		}
		return sl::ERROR_CODE::SUCCESS;
	}
}


sl::RecordingStatus ZEDController::get_camera_recording_status() const
{
	// TODO: Make more robust
	sl::RecordingStatus rec_status;
	if (is_camera_opened())
	{
		rec_status = camera->getRecordingStatus();
	}
	return rec_status;
}


sl::RecordingParameters ZEDController::get_camera_recording_parameters() const
{
	// TODO: Make more robust
	sl::RecordingParameters rec_params;
	if (is_camera_opened())
	{
		rec_params = camera->getRecordingParameters();
	}
	return rec_params;
}


std::ostream& operator<<(std::ostream& os, const ZEDController& ctrl)
{
	std::string cam_status = "Unbounded";
	sl::CameraInformation cam_info;
	// Get camera information
	if (ctrl.is_camera_opened())
	{
		cam_info = ctrl.get_camera_info();
		cam_status = "Opened";
	}
	else if (ctrl.is_camera_bounded() && !ctrl.is_camera_opened())
	{
		cam_status = "Bounded";
	}
	os << "[ZEDController] ID: " << std::to_string(ctrl.get_id()) << " | ";
	os << "CAMERA: " << cam_status << " ";
	os << cam_info.camera_model << " ";
	os << cam_info.serial_number << " | ";
	return os;
}

#include <zedutils/ZEDController.hpp>

#include <iostream>
#include <string>

ZEDController::ZEDController() : camera(nullptr)
{
	static unsigned int id = 0;
	id++;
	m_ID = id;
}


ZEDController::~ZEDController()
{
	if(camera_opened())
	{
		close_camera();
	}
	unbind_camera();
}


bool ZEDController::camera_bounded() const
{
	if (camera == nullptr)
	{
		return false;
	}
	return true;
}


bool ZEDController::camera_opened() const
{
	if (camera_bounded())
	{
		return camera->isOpened();
	}
	return false;
}


void ZEDController::bind_camera(sl::Camera* camera) 
{
	if (!camera_bounded())
	{
		// Assign new camera
		this->camera = camera;
	}
	return;
}


void ZEDController::unbind_camera()
{
	if (camera_bounded())
	{
		camera = nullptr;
	}
}


sl::ERROR_CODE ZEDController::open_camera(const sl::InitParameters param) const
{
	// Initialize to failure
	sl::ERROR_CODE error = sl::ERROR_CODE::FAILURE;
	if (camera_opened())
	{
		error = sl::ERROR_CODE::SUCCESS;
	}
	else if (camera_bounded() && !camera_opened())
	{
		error = camera->open(param);
	}
	return error;
}


void ZEDController::close_camera() const
{
	if (camera_bounded())
	{
		camera->close();
	}
	return;
}


sl::InitParameters ZEDController::get_init_parameters() const
{
	sl::InitParameters params;
	if (camera_opened())
	{
		params = camera->getInitParameters();
	}
	return params;
}


sl::RuntimeParameters ZEDController::get_runtime_parameters() const
{
	sl::RuntimeParameters params;
	if (camera_opened())
	{
		params = camera->getRuntimeParameters();
	}
	return params;
}


sl::CameraInformation ZEDController::get_camera_info() const
{
	//TODO: Make this function more robust?
	sl::CameraInformation info;
	if (camera_opened())
	{
		info = camera->getCameraInformation();
	}
	return info;
}


bool ZEDController::set_camera_settings(sl::VIDEO_SETTINGS settings)
{
	//TODO: Implement
}


int ZEDController::get_camera_settings(sl::VIDEO_SETTINGS settings) const
{
	//TODO: Implement
}


std::ostream& operator<<(std::ostream& os, const ZEDController& ctrl)
{
	std::string cam_status = "Unbounded";
	sl::CameraInformation cam_info;
	// Get camera information
	if (ctrl.camera_opened())
	{
		cam_info = ctrl.get_camera_info();
		cam_status = "Opened";
	}
	else if (ctrl.camera_bounded() && !ctrl.camera_opened())
	{
		cam_status = "Bounded";
	}
	os << "[ZEDController] ID: " << std::to_string(ctrl.get_id()) << " | ";
	os << "CAMERA: " << cam_status << " ";
	os << cam_info.camera_model << " ";
	os << cam_info.serial_number << " | ";
	return os;
}

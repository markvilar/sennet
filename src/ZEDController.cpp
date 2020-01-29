#include <zedutils/ZEDController.hpp>

#include <iostream>
#include <string>

ZEDController::ZEDController() : camera(nullptr)
{
}


ZEDController::~ZEDController()
{
	if(camera != nullptr)
	{
		sl::CameraInformation cam_info = camera->getCameraInformation();
		camera->close();
		camera = nullptr;
		std::cout << "Closed camera " << cam_info.serial_number
			<< " in ZEDController." << std::endl;
	}
}


bool ZEDController::has_camera_bounded()
{
	if (camera == nullptr)
	{
		return false;
	}
	return true;
}


void ZEDController::bind(sl::Camera* camera) 
{
	sl::CameraInformation cam_info;
	if (!has_camera_bounded())
	{
		this->camera = camera;
		cam_info = camera->getCameraInformation();
		std::cout << "Bounded camera " << cam_info.serial_number
			<< " in ZEDController." << std::endl;
	}
	else
	{
		cam_info = this->camera->getCameraInformation();
		std::cout << "ZEDController already bound to camera "
			<< cam_info.serial_number << "." << std::endl;
	}
}


void ZEDController::unbind()
{
	sl::CameraInformation cam_info;
	if (has_camera_bounded())
	{
		cam_info = camera->getCameraInformation();
		camera = nullptr;
		std::cout << "Unbounded camera " << cam_info.serial_number
			<< " in ZEDController." << std::endl;
	}
}



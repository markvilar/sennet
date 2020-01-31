#include <zedutils/ZEDio.hpp>

#include <iostream>
#include <string>

void print(std::string msg_prefix, const sl::ERROR_CODE err_code, 
		std::string msg_suffix)
{
	std::cout << "[Sample]";
	if (err_code != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << "[Error] ";
	}
	else
	{
		std::cout << " ";
	}

	std::cout << " ";

	if (err_code != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << " | " << toString(err_code) << " : ";
		std::cout << toVerbose(err_code);
	}

	if (!msg_suffix.empty())
	{
		std::cout << " " << msg_suffix;
	}

	std::cout << std::endl;
}


std::ostream& operator<<(std::ostream& os, const sl::InitParameters& params)
{
	os << "\nInitParameters:\n";
	os << " - Resolution:              " << params.camera_resolution << "\n";
	os << " - Fps:                     " << params.camera_fps << "\n";
	os << " - Image flip:              " << params.camera_image_flip << "\n";
	os << " - Svo real time mode:      " 
		<< params.svo_real_time_mode << "\n";
	os << " - Depth mode:              " 
		<< params.depth_mode << "\n";
	os << " - Depth stabilization:     " 
		<< params.depth_stabilization << "\n";
	os << " - Depth minimum dist.:     " 
		<< params.depth_minimum_distance << "\n";
	os << " - Depth maximum dist.:     " 
		<< params.depth_maximum_distance << "\n";
	os << " - Unit:                    " << params.coordinate_units << "\n";
	os << " - Coordinate system:       " << params.coordinate_system << "\n";
	os << " - SDK gpu id:              " << params.sdk_gpu_id << "\n";
	os << " - SDK verbose:             " << params.sdk_verbose << "\n";
	os << " - Sensors required:        " << params.sensors_required << "\n";
	os << " - Enable image enh.:       " 
		<< params.enable_image_enhancement << "\n";
	return os;
}


std::ostream& operator<<(std::ostream& os, const sl::RuntimeParameters& params)
{
	os << "\nRuntimeParameters:\n";
	os << " - Sensing mode:            " << params.sensing_mode << "\n";
	os << " - 3D reference frame:      " 
		<< params.measure3D_reference_frame << "\n";
	os << " - Enable depth:            " << params.enable_depth << "\n";
	os << " - Conf. thresh.:           " 
		<< params.confidence_threshold << "\n";
	os << " - Texture conf. thresh.:   " 
		<< params.textureness_confidence_threshold << "\n";
	return os;
}


std::ostream& operator<<(std::ostream& os, const sl::CameraInformation& params)
{
	os << "\nCameraInformation:\n";
	os << " - Serial number:           " << params.serial_number << "\n";
	os << " - Camera firmware version: " 
		<< params.camera_firmware_version << "\n";
	os << " - Sensor firmware version: " 
		<< params.sensors_firmware_version << "\n";
	os << " - Camera model:            " << params.camera_model << "\n";
	os << " - Input type:              " 
		<< params.input_type << "\n";
	os << " - Fps:                     " << params.camera_fps << "\n";
	os << " - Resolution:              " << params.camera_resolution << "\n";
	return os;
}


std::ostream& operator<<(std::ostream& os, const sl::Resolution& res)
{
	os << res.width << "x" << res.height << " (WxH)\n";
	return os;
}

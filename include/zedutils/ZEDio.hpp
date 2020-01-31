#include <sl/Camera.hpp>

#include <iostream>
#include <string>


void print(std::string msg_prefix, const sl::ERROR_CODE err_code, 
		std::string msg_suffix);


std::ostream& operator<<(std::ostream& os, const sl::InitParameters& params);
std::ostream& operator<<(std::ostream& os, const sl::RuntimeParameters& params);
std::ostream& operator<<(std::ostream& os, const sl::CameraInformation& params);
std::ostream& operator<<(std::ostream& os, const sl::Resolution& res);

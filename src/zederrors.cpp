#include <zedutils/zederrors.hpp>

#include <iostream>
#include <string>

void print(std::string msg_prefix, sl::ERROR_CODE err_code, 
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

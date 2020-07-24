#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include <sennet/sennet.hpp>

#include <sennet/zed/conversion.hpp>
#include <sennet/zed/recorder.hpp>
#include <sennet/zed/io.hpp>

void test_params()
{
	sennet::zed::init_params init_params;
	sennet::zed::recording_params rec_params;
	sennet::zed::runtime_params run_params;

	std::cout << init_params << "\n";
	std::cout << rec_params << "\n";
	std::cout << run_params << "\n";
}

void test_to_stereolabs()
{
	sennet::ref<sennet::zed::init_params> init_params;
	sennet::ref<sennet::zed::recording_params> rec_params;
	sennet::ref<sennet::zed::runtime_params> run_params;

	std::cout << *init_params << "\n";
	std::cout << *to_stereolabs(init_params) << "\n";

	std::cout << *rec_params << "\n";
	std::cout << *to_stereolabs(rec_params) << "\n";

	std::cout << *run_params << "\n";
	std::cout << *to_stereolabs(run_params) << "\n";
}

void test_to_sennet()
{
	sennet::ref<sl::InitParameters> init_params;
	sennet::ref<sl::RecordingParameters> rec_params;
	sennet::ref<sl::RuntimeParameters> run_params;

	std::cout << *init_params << "\n";
	std::cout << *to_sennet(init_params) << "\n";	

	std::cout << *rec_params << "\n";
	std::cout << *to_sennet(rec_params) << "\n";

	std::cout << *run_params << "\n";
	std::cout << *to_sennet(run_params) << "\n";

}

void sleep_this_thread(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void test_recorder()
{
	auto handle = sennet::create_scope<sennet::zed::recorder>();
	sleep_this_thread(100);
	handle->start_record();
	sleep_this_thread(1000);

	auto init_params = handle->get_init_params();
	auto zed_init_params = handle->get_zed_init_params();
	if (init_params)
	{
		SN_INFO(init_params->to_string());
	}
	if (zed_init_params)
	{
		SN_INFO(zed_init_params->to_string());
	}

	int count = 0;
	int n = 10;

	while (count < n)
	{
		auto image = handle->get_image(sennet::zed::view::side_by_side);
		if (image)
		{
			std::cout << *image << "\n";
			std::cout << static_cast<int>(image->get_pixel(640, 360, 0))
				<< ", " 
				<< static_cast<int>(image->get_pixel(640, 360, 1))
				<< ", " 
				<< static_cast<int>(image->get_pixel(640, 360, 2))
				<< ", " 
				<< static_cast<int>(image->get_pixel(640, 360, 3))
				<< "\n";
			count++;
			sleep_this_thread(1000);
		}
	}
}

int main(int argc, char* argv[])
{
	sennet::log::init();

	test_recorder();

	return 0;
}

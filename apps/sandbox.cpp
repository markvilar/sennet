#define SN_DEBUG
#define SN_ENABLE_ASSERTS

#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include <sennet/sennet.hpp>

#include <sennet/zed/conversion.hpp>
#include <sennet/zed/zed_recorder.hpp>
#include <sennet/types/zed.hpp>

void test_params()
{
	sennet::zed::depth_init_params depth_params;
	sennet::zed::init_params init_params(depth_params);
	sennet::zed::recording_params rec_params;
	sennet::zed::runtime_params run_params;
	std::cout << depth_params << "\n";
	std::cout << init_params << "\n";
	std::cout << rec_params << "\n";
	std::cout << run_params << "\n";
}

int main()
{	
	// Initialize log and handler.
	sennet::log::init();

	auto window = sennet::window::create();

	if (!window)
		std::cout << "Window is null!\n";

	//test_params();
	return 0;
}

#include <iostream>

#include <sl/Camera.hpp>

#include <sennet/sennet.hpp>

#include <sennet/zed/conversion.hpp>
#include <sennet/zed/io.hpp>
#include <sennet/zed/zed_recorder.hpp>

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

void test_to_stereolabs()
{
	sennet::zed::depth_init_params depth_params;
	sennet::zed::init_params init_params(depth_params);
	sennet::zed::recording_params rec_params;
	sennet::zed::runtime_params run_params;

	std::cout << init_params << "\n";
	std::cout << to_stereolabs(init_params) << "\n";

	std::cout << rec_params << "\n";
	std::cout << to_stereolabs(rec_params) << "\n";

	std::cout << run_params << "\n";
	std::cout << to_stereolabs(run_params) << "\n";
}

void test_to_sennet()
{
	sl::InitParameters init_params;
	sl::RecordingParameters rec_params;
	sl::RuntimeParameters run_params;

	std::cout << init_params << "\n";
	std::cout << to_sennet(init_params) << "\n";	

	std::cout << rec_params << "\n";
	std::cout << to_sennet(rec_params) << "\n";

	std::cout << run_params << "\n";
	std::cout << to_sennet(run_params) << "\n";

}

int main(int argc, char* argv[])
{
	sennet::log::init();

	test_params();
	test_to_stereolabs();
	test_to_sennet();

	return 0;
}

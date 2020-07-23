#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include <sennet/sennet.hpp>

#include <sennet/zed/conversion.hpp>
#include <sennet/zed/io.hpp>
#include <sennet/zed/zed_recorder.hpp>

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

void test_recorder()
{
	sennet::zed_recorder handle;

	handle.init();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	handle.start_record();
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	handle.stop_record();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	handle.shutdown();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	handle.init();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	handle.start_record();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main(int argc, char* argv[])
{
	sennet::log::init();

	test_recorder();

	return 0;
}

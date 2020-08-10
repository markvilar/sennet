#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include <Sennet/Sennet.hpp>

#include <Sennet/ZED/Conversion.hpp>
#include <Sennet/ZED/Recorder.hpp>
#include <Sennet/ZED/IO.hpp>

void test_params()
{
	Sennet::ZED::init_params init_params;
	Sennet::ZED::recording_params rec_params;
	Sennet::ZED::runtime_params run_params;

	std::cout << init_params << "\n";
	std::cout << rec_params << "\n";
	std::cout << run_params << "\n";
}

void test_SennetToStereolabs()
{
	Sennet::Ref<Sennet::ZED::init_params> init_params;
	Sennet::Ref<Sennet::ZED::recording_params> rec_params;
	Sennet::Ref<Sennet::ZED::runtime_params> run_params;

	std::cout << *init_params << "\n";
	std::cout << *SennetToStereolabs(init_params) << "\n";

	std::cout << *rec_params << "\n";
	std::cout << *SennetToStereolabs(rec_params) << "\n";

	std::cout << *run_params << "\n";
	std::cout << *SennetToStereolabs(run_params) << "\n";
}

void test_StereolabsToSennet()
{
	Sennet::Ref<sl::InitParameters> init_params;
	Sennet::Ref<sl::RecordingParameters> rec_params;
	Sennet::Ref<sl::RuntimeParameters> run_params;

	std::cout << *init_params << "\n";
	std::cout << *StereolabsToSennet(init_params) << "\n";	

	std::cout << *rec_params << "\n";
	std::cout << *StereolabsToSennet(rec_params) << "\n";

	std::cout << *run_params << "\n";
	std::cout << *StereolabsToSennet(run_params) << "\n";

}

void SleepThisThread(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void testRecorder()
{
	auto handle = Sennet::CreateScope<Sennet::ZED::Recorder>();
	handle->StartRecord();
	SleepThisThread(1000);

	auto initParameters = handle->GetInitParameters();
	auto ZEDInitParameters = handle->GetZEDInitParameters();
	if (initParameters)
	{
		SN_INFO(initParameters->ToString());
	}
	if (ZEDInitParameters)
	{
		SN_INFO(ZEDInitParameters->ToString());
	}

	int count = 0;
	int n = 10;

	while (count < n)
	{
		auto image = handle->GetImage(Sennet::ZED::view::side_by_side);
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
			SleepThisThread(1000);
		}
	}
}

int main(int argc, char* argv[])
{
	Sennet::Log::Init();

	testRecorder();

	return 0;
}

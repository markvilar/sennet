#include <chrono>
#include <thread>

#include "Sennet/Sennet.hpp"

int main()
{
	Sennet::Log::Init();

	Sennet::Synchronizer::Get().BeginSession("Test");

	for (int n = 0; n < 10; n++)
	{
		SN_INFO("Getting timestamp.");
		Sennet::Synchronizer::Get().WriteEntry(
			Sennet::Timestamp("Local"), Sennet::Timestamp("UHI"));
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}

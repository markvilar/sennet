#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include <sennet/io.hpp>
#include <sennet/log.hpp>
#include <sennet/conversion/zed.hpp>
#include <sennet/handlers/zed_recorder.hpp>
#include <sennet/types/zed.hpp>

int main()
{	
	// Initialize log and handler.
	sennet::log::init();

	return 0;
}

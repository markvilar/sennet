#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include <sennet/io.hpp>
#include <sennet/log.hpp>
#include <sennet/conversion/zed.hpp>
#include <sennet/handlers/zed_recorder.hpp>
#include <sennet/types/zed.hpp>

void print_coord_sys()
{
	std::cout << sennet::zed::coordinate_system::image << "\n";
	std::cout << sennet::zed::coordinate_system::left_handed_y_up << "\n";
	std::cout << sennet::zed::coordinate_system::right_handed_y_up << "\n";
	std::cout << sennet::zed::coordinate_system::right_handed_z_up << "\n";
	std::cout << sennet::zed::coordinate_system::left_handed_z_up << "\n";
	std::cout << sennet::zed::coordinate_system::right_handed_z_up_x_fwd 
		<< "\n";
}

int main()
{	
	// Initialize log and handler.
	sennet::log::init();

	print_coord_sys();
	return 0;
}

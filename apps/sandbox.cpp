#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include <sennet/io.hpp>
#include <sennet/log.hpp>
#include <sennet/conversion/zed.hpp>
#include <sennet/handlers/zed_recorder.hpp>
#include <sennet/types/zed.hpp>

void test_types()
{
	std::cout << "[coordinate_system]\n";	
	std::cout << sennet::zed::coordinate_system::none << "\n";
	std::cout << sennet::zed::coordinate_system::image << "\n";
	std::cout << sennet::zed::coordinate_system::left_handed_y_up << "\n";
	std::cout << sennet::zed::coordinate_system::right_handed_y_up << "\n";
	std::cout << sennet::zed::coordinate_system::right_handed_z_up << "\n";
	std::cout << sennet::zed::coordinate_system::left_handed_z_up << "\n";
	std::cout << sennet::zed::coordinate_system::right_handed_z_up_x_fwd 
		<< "\n";

	std::cout << "[depth_mode]\n";
	std::cout << sennet::zed::depth_mode::none << "\n";
	std::cout << sennet::zed::depth_mode::performance << "\n";
	std::cout << sennet::zed::depth_mode::quality << "\n";
	std::cout << sennet::zed::depth_mode::ultra << "\n";

	std::cout << "[reference_frame]\n";
	std::cout << sennet::zed::reference_frame::none << "\n";
	std::cout << sennet::zed::reference_frame::world << "\n";
	std::cout << sennet::zed::reference_frame::camera << "\n";
	
	std::cout << "[resolution]\n";
	std::cout << sennet::zed::resolution::none << "\n";
	std::cout << sennet::zed::resolution::hd2k << "\n";
	std::cout << sennet::zed::resolution::hd1080 << "\n";
	std::cout << sennet::zed::resolution::hd720 << "\n";
	std::cout << sennet::zed::resolution::vga << "\n";

	std::cout << "[svo_compression_mode]\n";
	std::cout << sennet::zed::svo_compression_mode::none << "\n";
	std::cout << sennet::zed::svo_compression_mode::lossless << "\n";
	std::cout << sennet::zed::svo_compression_mode::h264 << "\n";
	std::cout << sennet::zed::svo_compression_mode::h265 << "\n";

	std::cout << "[sensing_mode]\n";
	std::cout << sennet::zed::sensing_mode::none << "\n";
	std::cout << sennet::zed::sensing_mode::standard << "\n";
	std::cout << sennet::zed::sensing_mode::fill << "\n";

	std::cout << "[unit]\n";
	std::cout << sennet::zed::unit::none << "\n";
	std::cout << sennet::zed::unit::millimeter << "\n";
	std::cout << sennet::zed::unit::centimeter << "\n";
	std::cout << sennet::zed::unit::meter << "\n";
	std::cout << sennet::zed::unit::inch << "\n";
	std::cout << sennet::zed::unit::foot << "\n";

	std::cout << "[video_settings]\n";
	std::cout << sennet::zed::video_settings::none << "\n";
	std::cout << sennet::zed::video_settings::brightness << "\n";
	std::cout << sennet::zed::video_settings::contrast << "\n";
	std::cout << sennet::zed::video_settings::hue << "\n";
	std::cout << sennet::zed::video_settings::saturation << "\n";
	std::cout << sennet::zed::video_settings::sharpness << "\n";
	std::cout << sennet::zed::video_settings::gain << "\n";
	std::cout << sennet::zed::video_settings::exposure << "\n";
	std::cout << sennet::zed::video_settings::aec_agc << "\n";
	std::cout << sennet::zed::video_settings::whitebalance_temperature 
		<< "\n";
	std::cout << sennet::zed::video_settings::whitebalance_auto << "\n";
	std::cout << sennet::zed::video_settings::led_status << "\n";

	std::cout << "[view]\n";
	std::cout << sennet::zed::view::none << "\n";
	std::cout << sennet::zed::view::left << "\n";
	std::cout << sennet::zed::view::right << "\n";
	std::cout << sennet::zed::view::left_gray << "\n";
	std::cout << sennet::zed::view::right_gray << "\n";
	std::cout << sennet::zed::view::left_unrectified << "\n";
	std::cout << sennet::zed::view::right_unrectified << "\n";
	std::cout << sennet::zed::view::left_unrectified_gray << "\n";
	std::cout << sennet::zed::view::right_unrectified_gray << "\n";
	std::cout << sennet::zed::view::side_by_side << "\n";
}

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

	test_types();
	test_params();
	return 0;
}

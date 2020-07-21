#include <sennet/zed/conversion.hpp>

sl::VIEW to_stereolabs(const sennet::zed::view& x)
{
	switch (x)
	{
		case sennet::zed::view::left:
			return sl::VIEW::LEFT;
		case sennet::zed::view::right:
			return sl::VIEW::RIGHT;
		case sennet::zed::view::left_gray:
			return sl::VIEW::LEFT_GRAY;
		case sennet::zed::view::right_gray:
			return sl::VIEW::RIGHT_GRAY;
		case sennet::zed::view::left_unrectified:
			return sl::VIEW::LEFT_UNRECTIFIED;
		case sennet::zed::view::right_unrectified:
			return sl::VIEW::RIGHT_UNRECTIFIED;
		case sennet::zed::view::left_unrectified_gray:
			return sl::VIEW::LEFT_UNRECTIFIED_GRAY;
		case sennet::zed::view::right_unrectified_gray:
			return sl::VIEW::RIGHT_UNRECTIFIED_GRAY;
		case sennet::zed::view::side_by_side:
			return sl::VIEW::SIDE_BY_SIDE;
		default:
			return sl::VIEW::LAST;
	}
}

sl::RESOLUTION to_stereolabs(const sennet::zed::resolution& x)
{
	switch (x)
	{
		case sennet::zed::resolution::hd2k:
			return sl::RESOLUTION::HD2K;
		case sennet::zed::resolution::hd1080:
			return sl::RESOLUTION::HD1080;
		case sennet::zed::resolution::hd720:
			return sl::RESOLUTION::HD720;
		case sennet::zed::resolution::vga:
			return sl::RESOLUTION::VGA;
		default:
			return sl::RESOLUTION::LAST;
	}
}

sl::VIDEO_SETTINGS to_stereolabs(const sennet::zed::video_settings& x)
{
	switch (x)
	{
		case sennet::zed::video_settings::brightness:
			return sl::VIDEO_SETTINGS::BRIGHTNESS;
		case sennet::zed::video_settings::contrast:
			return sl::VIDEO_SETTINGS::CONTRAST;
		case sennet::zed::video_settings::hue:
			return sl::VIDEO_SETTINGS::HUE;
		case sennet::zed::video_settings::saturation:
			return sl::VIDEO_SETTINGS::SATURATION;
		case sennet::zed::video_settings::sharpness:
			return sl::VIDEO_SETTINGS::SHARPNESS;
		case sennet::zed::video_settings::gain:
			return sl::VIDEO_SETTINGS::GAIN;
		case sennet::zed::video_settings::exposure:
			return sl::VIDEO_SETTINGS::EXPOSURE;
		case sennet::zed::video_settings::aec_agc:
			return sl::VIDEO_SETTINGS::AEC_AGC;
		case sennet::zed::video_settings::whitebalance_temperature:
			return sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE;
		case sennet::zed::video_settings::whitebalance_auto:
			return sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO;
		case sennet::zed::video_settings::led_status:
			return sl::VIDEO_SETTINGS::LED_STATUS;
		default:
			return sl::VIDEO_SETTINGS::LAST;
	}
}

sl::DEPTH_MODE to_stereolabs(const sennet::zed::depth_mode& x)
{
	switch (x)
	{
		case sennet::zed::depth_mode::performance:
			return sl::DEPTH_MODE::PERFORMANCE;
		case sennet::zed::depth_mode::quality:
			return sl::DEPTH_MODE::QUALITY;
		case sennet::zed::depth_mode::ultra:
			return sl::DEPTH_MODE::ULTRA;
		default:
			return sl::DEPTH_MODE::LAST;
	}
}

sl::UNIT to_stereolabs(const sennet::zed::unit& x)
{
	switch (x)
	{
		case sennet::zed::unit::millimeter:
			return sl::UNIT::MILLIMETER;
		case sennet::zed::unit::centimeter:
			return sl::UNIT::CENTIMETER;
		case sennet::zed::unit::meter:
			return sl::UNIT::METER;
		case sennet::zed::unit::inch:
			return sl::UNIT::INCH;
		case sennet::zed::unit::foot:
			return sl::UNIT::FOOT;
		default:
			return sl::UNIT::LAST;
	}
}

sl::SVO_COMPRESSION_MODE to_stereolabs(
	const sennet::zed::svo_compression_mode& x)
{
	switch (x)
	{
		case sennet::zed::svo_compression_mode::lossless:
			return sl::SVO_COMPRESSION_MODE::LOSSLESS;
		case sennet::zed::svo_compression_mode::h264:
			return sl::SVO_COMPRESSION_MODE::H264;
		case sennet::zed::svo_compression_mode::h265:
			return sl::SVO_COMPRESSION_MODE::H265;
		default:
			return sl::SVO_COMPRESSION_MODE::LAST;
	}
}

sl::SENSING_MODE to_stereolabs(const sennet::zed::sensing_mode& x)
{
	switch (x)
	{
		case sennet::zed::sensing_mode::standard:
			return sl::SENSING_MODE::STANDARD;
		case sennet::zed::sensing_mode::fill:
			return sl::SENSING_MODE::FILL;
		default:
			return sl::SENSING_MODE::LAST;
	}
}

sl::REFERENCE_FRAME to_stereolabs(const sennet::zed::reference_frame& x)
{
	switch (x)
	{
		case sennet::zed::reference_frame::world: 
			return sl::REFERENCE_FRAME::WORLD;
		case sennet::zed::reference_frame::camera: 
			return sl::REFERENCE_FRAME::CAMERA;
		default: 
			return sl::REFERENCE_FRAME::LAST;
	}
}

sl::COORDINATE_SYSTEM to_stereolabs(const sennet::zed::coordinate_system& x)
{
	switch (x)
	{
		case sennet::zed::coordinate_system::image:
			return sl::COORDINATE_SYSTEM::IMAGE;
		case sennet::zed::coordinate_system::left_handed_y_up:
			return sl::COORDINATE_SYSTEM::LEFT_HANDED_Y_UP;
		case sennet::zed::coordinate_system::right_handed_y_up:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP;
		case sennet::zed::coordinate_system::right_handed_z_up:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP;
		case sennet::zed::coordinate_system::left_handed_z_up:
			return sl::COORDINATE_SYSTEM::LEFT_HANDED_Z_UP;
		case sennet::zed::coordinate_system::right_handed_z_up_x_fwd:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP_X_FWD;
		default:
			return sl::COORDINATE_SYSTEM::LAST;
	}
}

std::shared_ptr<sl::Mat> to_stereolabs(const sennet::zed::image& x)
{
	auto mat_type = sl::MAT_TYPE::U8_C1;
	switch (x.get_channels())
	{
		case 1:
			mat_type = sl::MAT_TYPE::U8_C1;
			break;
		case 2:
			mat_type = sl::MAT_TYPE::U8_C2;
			break;
		case 3:
			mat_type = sl::MAT_TYPE::U8_C3;
			break;
		case 4:
			mat_type = sl::MAT_TYPE::U8_C4;
			break;
		default:
			return nullptr;
	}
	return std::make_shared<sl::Mat>(x.get_width(), x.get_height(), 
		mat_type, (sl::uchar1*)x.get_ptr(), x.get_channels());
}

sl::InitParameters to_stereolabs(const sennet::zed::init_params& ip)
{
	sl::InitParameters cnv;
	
	// Depth parameters.
	auto dp = ip.get_depth_params();
	cnv.depth_mode = ::to_stereolabs(dp.get_depth_mode());
	cnv.coordinate_units = ::to_stereolabs(dp.get_coord_units());
	cnv.coordinate_system = ::to_stereolabs(dp.get_coord_sys());
	cnv.depth_stabilization = dp.get_depth_stab();
	cnv.depth_minimum_distance = dp.get_min_depth();
	cnv.depth_maximum_distance = dp.get_max_depth();
	cnv.enable_right_side_measure = dp.right_depth_enabled();

	// Generic parameters.
	cnv.camera_resolution = ::to_stereolabs(ip.get_resolution());
	cnv.camera_fps = ip.get_camera_fps();
	cnv.enable_image_enhancement = ip.img_enhance_enabled();
	cnv.camera_disable_self_calib = ip.self_calib_disabled();
	cnv.sdk_verbose = ip.is_sdk_verbose();
	cnv.sensors_required = ip.sensors_required();

	return cnv;
}

sl::RecordingParameters to_stereolabs(const sennet::zed::recording_params& rp)
{
	sl::RecordingParameters cnv;
	cnv.video_filename = sl::String(rp.get_filename().c_str());
	cnv.compression_mode = to_stereolabs(rp.get_compression_mode());

	return cnv;
}

sl::RuntimeParameters to_stereolabs(const sennet::zed::runtime_params& rp)
{
	sl::RuntimeParameters cnv;
	cnv.sensing_mode = to_stereolabs(rp.get_sensing_mode());
	cnv.measure3D_reference_frame = to_stereolabs(rp.get_reference_frame());
	cnv.enable_depth = rp.is_depth_enabled();
	cnv.confidence_threshold = rp.get_confidence_threshold();
	cnv.textureness_confidence_threshold =
		rp.get_texture_confidence_threshold();
	return cnv;
}



// To ZED conversion functions.

sennet::zed::view to_sennet(const sl::VIEW& x)
{
	typedef sennet::zed::view zed_view;
	switch (x)
	{
		case sl::VIEW::LEFT:
			return zed_view::left;
		case sl::VIEW::RIGHT:
			return zed_view::right;
		case sl::VIEW::LEFT_GRAY:
			return zed_view::left_gray;
		case sl::VIEW::RIGHT_GRAY:
			return zed_view::right_gray;
		case sl::VIEW::LEFT_UNRECTIFIED:
			return zed_view::left_unrectified;
		case sl::VIEW::RIGHT_UNRECTIFIED:
			return zed_view::right_unrectified;
		case sl::VIEW::LEFT_UNRECTIFIED_GRAY:
			return zed_view::left_unrectified_gray;
		case sl::VIEW::RIGHT_UNRECTIFIED_GRAY:
			return zed_view::right_unrectified_gray;
		case sl::VIEW::SIDE_BY_SIDE:
			return zed_view::side_by_side;
		default:
			return zed_view::none;
	}
}

sennet::zed::resolution to_sennet(const sl::RESOLUTION& x)
{
	typedef sennet::zed::resolution zed_resolution;
	switch (x)
	{
		case sl::RESOLUTION::HD2K:
			return zed_resolution::hd2k;
		case sl::RESOLUTION::HD1080:
			return zed_resolution::hd1080;
		case sl::RESOLUTION::HD720:
			return zed_resolution::hd720;
		case sl::RESOLUTION::VGA:
			return zed_resolution::vga;
		default:
			return zed_resolution::none;
	}
}

sennet::zed::video_settings to_sennet(const sl::VIDEO_SETTINGS& x)
{
	typedef sennet::zed::video_settings zed_video_settings;
	switch (x)
	{
		case sl::VIDEO_SETTINGS::BRIGHTNESS:
			return zed_video_settings::brightness;
		case sl::VIDEO_SETTINGS::CONTRAST:
			return zed_video_settings::contrast;
		case sl::VIDEO_SETTINGS::HUE:
			return zed_video_settings::hue;
		case sl::VIDEO_SETTINGS::SATURATION:
			return zed_video_settings::saturation;
		case sl::VIDEO_SETTINGS::SHARPNESS:
			return zed_video_settings::sharpness;
		case sl::VIDEO_SETTINGS::GAIN:
			return zed_video_settings::gain;
		case sl::VIDEO_SETTINGS::EXPOSURE:
			return zed_video_settings::exposure;
		case sl::VIDEO_SETTINGS::AEC_AGC:
			return zed_video_settings::aec_agc;
		case sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE:
			return zed_video_settings::whitebalance_temperature;
		case sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO:
			return zed_video_settings::whitebalance_auto;
		case sl::VIDEO_SETTINGS::LED_STATUS:
			return zed_video_settings::led_status;
		default:
			return zed_video_settings::none;
	}
}

sennet::zed::depth_mode to_sennet(const sl::DEPTH_MODE& x)
{
	typedef sennet::zed::depth_mode zed_depth_mode;
	switch (x)
	{
		case sl::DEPTH_MODE::PERFORMANCE:
			return zed_depth_mode::performance;
		case sl::DEPTH_MODE::QUALITY:
			return zed_depth_mode::quality;
		case sl::DEPTH_MODE::ULTRA:
			return zed_depth_mode::ultra;
		default:
			return zed_depth_mode::none;
	}
}

sennet::zed::unit to_sennet(const sl::UNIT& x)
{
	typedef sennet::zed::unit zed_unit;
	switch (x)
	{
		case sl::UNIT::MILLIMETER:
			return zed_unit::millimeter;		
		case sl::UNIT::CENTIMETER:
			return zed_unit::centimeter;
		case sl::UNIT::METER:
			return zed_unit::meter;
		case sl::UNIT::INCH:
			return zed_unit::inch;
		case sl::UNIT::FOOT:
			return zed_unit::foot;
		default:
			return zed_unit::none;
	}
}

sennet::zed::svo_compression_mode to_sennet(const sl::SVO_COMPRESSION_MODE& x)
{
	typedef sennet::zed::svo_compression_mode zed_svo_compression_mode;
	switch (x)
	{
		case sl::SVO_COMPRESSION_MODE::LOSSLESS:
			return zed_svo_compression_mode::lossless;
		case sl::SVO_COMPRESSION_MODE::H264:
			return zed_svo_compression_mode::h264;
		case sl::SVO_COMPRESSION_MODE::H265:
			return zed_svo_compression_mode::h265;
		default:
			return zed_svo_compression_mode::none;
	}
}

sennet::zed::sensing_mode to_sennet(const sl::SENSING_MODE& x)
{
	typedef sennet::zed::sensing_mode zed_sensing_mode;
	switch (x)
	{
		case sl::SENSING_MODE::STANDARD:
			return zed_sensing_mode::standard;
		case sl::SENSING_MODE::FILL:
			return zed_sensing_mode::fill;
		default:
			return zed_sensing_mode::none;
	}
}

sennet::zed::reference_frame to_sennet(const sl::REFERENCE_FRAME& x)
{
	typedef sennet::zed::reference_frame zed_ref_frame;
	switch (x)
	{
		case sl::REFERENCE_FRAME::WORLD:
			return zed_ref_frame::world;		
		case sl::REFERENCE_FRAME::CAMERA:
			return zed_ref_frame::camera;
		default:
			return zed_ref_frame::none;
	}
}

sennet::zed::coordinate_system to_sennet(const sl::COORDINATE_SYSTEM& x)
{
	typedef sennet::zed::coordinate_system zed_coord_sys;
	switch (x)
	{
		case sl::COORDINATE_SYSTEM::IMAGE:
			return zed_coord_sys::image;
		case sl::COORDINATE_SYSTEM::LEFT_HANDED_Y_UP:
			return zed_coord_sys::left_handed_y_up;
		case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP:
			return zed_coord_sys::right_handed_y_up;
		case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP:
			return zed_coord_sys::right_handed_z_up;
		case sl::COORDINATE_SYSTEM::LEFT_HANDED_Z_UP:
			return zed_coord_sys::left_handed_z_up;
		case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP_X_FWD:
			return zed_coord_sys::right_handed_z_up_x_fwd;
		default:
			return zed_coord_sys::none;
	}
}

std::shared_ptr<sennet::zed::image> to_sennet(const sl::Mat& m)
{
	size_t channels = 0;
	switch (m.getDataType())
	{
		case sl::MAT_TYPE::U8_C1:
			channels = 1;
			break;
		case sl::MAT_TYPE::U8_C2:
			channels = 2;
			break;
		case sl::MAT_TYPE::U8_C3:
			channels = 3;
			break;
		case sl::MAT_TYPE::U8_C4:
			channels = 4;
			break;
		default:
			return nullptr;
	}
	return std::make_shared<sennet::zed::image>(m.getPtr<unsigned char>(),
		m.getWidth(), m.getHeight(), m.getChannels());
}

sennet::zed::init_params to_sennet(const sl::InitParameters& ip)
{
	sennet::zed::depth_init_params dp(
		to_sennet(ip.depth_mode),
		to_sennet(ip.coordinate_units),
		to_sennet(ip.coordinate_system),
		ip.depth_stabilization,
		ip.depth_minimum_distance,
		ip.depth_maximum_distance,
		ip.enable_right_side_measure);

	sennet::zed::init_params cnv(
		dp,
		to_sennet(ip.camera_resolution),
		ip.camera_fps,
		ip.enable_image_enhancement,
		ip.camera_disable_self_calib,
		ip.sdk_verbose,
		ip.sensors_required);

	return cnv;
}

sennet::zed::recording_params to_sennet(const sl::RecordingParameters& rp)
{
	sennet::zed::recording_params cnv(
		std::string(rp.video_filename.get()),
		to_sennet(rp.compression_mode));
	return cnv;
}

sennet::zed::runtime_params to_sennet(const sl::RuntimeParameters& rp)
{
	sennet::zed::runtime_params cnv(
		to_sennet(rp.sensing_mode),
		to_sennet(rp.measure3D_reference_frame),
		rp.enable_depth,
		rp.confidence_threshold,
		rp.textureness_confidence_threshold);
	return cnv;
}

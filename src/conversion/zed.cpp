#include <sennet/conversion/zed.hpp>

namespace sennet
{

sl::VIEW to_stereolabs(const zed::view& x)
{
	switch (x)
	{
		case zed::view::left:
			return sl::VIEW::LEFT;
		case zed::view::right:
			return sl::VIEW::RIGHT;
		case zed::view::left_gray:
			return sl::VIEW::LEFT_GRAY;
		case zed::view::right_gray:
			return sl::VIEW::RIGHT_GRAY;
		case zed::view::left_unrectified:
			return sl::VIEW::LEFT_UNRECTIFIED;
		case zed::view::right_unrectified:
			return sl::VIEW::RIGHT_UNRECTIFIED;
		case zed::view::left_unrectified_gray:
			return sl::VIEW::LEFT_UNRECTIFIED_GRAY;
		case zed::view::right_unrectified_gray:
			return sl::VIEW::RIGHT_UNRECTIFIED_GRAY;
		case zed::view::side_by_side:
			return sl::VIEW::SIDE_BY_SIDE;
		default:
			return sl::VIEW::LAST;
	}
}

sl::RESOLUTION to_stereolabs(const zed::resolution& x)
{
	switch (x)
	{
		case zed::resolution::hd2k:
			return sl::RESOLUTION::HD2K;
		case zed::resolution::hd1080:
			return sl::RESOLUTION::HD1080;
		case zed::resolution::hd720:
			return sl::RESOLUTION::HD720;
		case zed::resolution::vga:
			return sl::RESOLUTION::VGA;
		default:
			return sl::RESOLUTION::LAST;
	}
}

sl::VIDEO_SETTINGS to_stereolabs(const zed::video_settings& x)
{
	switch (x)
	{
		case zed::video_settings::brightness:
			return sl::VIDEO_SETTINGS::BRIGHTNESS;
		case zed::video_settings::contrast:
			return sl::VIDEO_SETTINGS::CONTRAST;
		case zed::video_settings::hue:
			return sl::VIDEO_SETTINGS::HUE;
		case zed::video_settings::saturation:
			return sl::VIDEO_SETTINGS::SATURATION;
		case zed::video_settings::sharpness:
			return sl::VIDEO_SETTINGS::SHARPNESS;
		case zed::video_settings::gain:
			return sl::VIDEO_SETTINGS::GAIN;
		case zed::video_settings::exposure:
			return sl::VIDEO_SETTINGS::EXPOSURE;
		case zed::video_settings::aec_agc:
			return sl::VIDEO_SETTINGS::AEC_AGC;
		case zed::video_settings::whitebalance_temperature:
			return sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE;
		case zed::video_settings::whitebalance_auto:
			return sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO;
		case zed::video_settings::led_status:
			return sl::VIDEO_SETTINGS::LED_STATUS;
		default:
			return sl::VIDEO_SETTINGS::LAST;
	}
}

sl::DEPTH_MODE to_stereolabs(const zed::depth_mode& x)
{
	switch (x)
	{
		case zed::depth_mode::performance:
			return sl::DEPTH_MODE::PERFORMANCE;
		case zed::depth_mode::quality:
			return sl::DEPTH_MODE::QUALITY;
		case zed::depth_mode::ultra:
			return sl::DEPTH_MODE::ULTRA;
		default:
			return sl::DEPTH_MODE::LAST;
	}
}

sl::UNIT to_stereolabs(const zed::unit& x)
{
	switch (x)
	{
		case zed::unit::millimeter:
			return sl::UNIT::MILLIMETER;
		case zed::unit::centimeter:
			return sl::UNIT::CENTIMETER;
		case zed::unit::meter:
			return sl::UNIT::METER;
		case zed::unit::inch:
			return sl::UNIT::INCH;
		case zed::unit::foot:
			return sl::UNIT::FOOT;
		default:
			return sl::UNIT::LAST;
	}
}

sl::SVO_COMPRESSION_MODE to_stereolabs(const zed::svo_compression_mode& x)
{
	switch (x)
	{
		case zed::svo_compression_mode::lossless:
			return sl::SVO_COMPRESSION_MODE::LOSSLESS;
		case zed::svo_compression_mode::h264:
			return sl::SVO_COMPRESSION_MODE::H264;
		case zed::svo_compression_mode::h265:
			return sl::SVO_COMPRESSION_MODE::H265;
		default:
			return sl::SVO_COMPRESSION_MODE::LAST;
	}
}

sl::SENSING_MODE to_stereolabs(const zed::sensing_mode& x)
{
	switch (x)
	{
		case zed::sensing_mode::standard:
			return sl::SENSING_MODE::STANDARD;
		case zed::sensing_mode::fill:
			return sl::SENSING_MODE::FILL;
		default:
			return sl::SENSING_MODE::LAST;
	}
}

sl::REFERENCE_FRAME to_stereolabs(const zed::reference_frame& x)
{
	switch (x)
	{
		case zed::reference_frame::world: 
			return sl::REFERENCE_FRAME::CAMERA;
		case zed::reference_frame::camera: 
			return sl::REFERENCE_FRAME::WORLD;
		default: 
			return sl::REFERENCE_FRAME::LAST;
	}
}

std::shared_ptr<sl::Mat> to_stereolabs(const zed::image& x)
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
	return std::make_shared<sl::Mat>(x.get_width(), x.get_height(), mat_type, 
		(sl::uchar1*)x.get_ptr(), x.get_channels());
}

sl::InitParameters to_stereolabs(const zed::init_params& x)
{
	// TODO: Implement.
}

sl::RecordingParameters to_stereolabs(const zed::recording_params& x)
{
	// TODO: Implement.
}

sl::RuntimeParameters to_stereolabs(const zed::runtime_params& x)
{
	// TODO: Implement.
}

sl::COORDINATE_SYSTEM to_stereolabs(const zed::coordinate_system& x)
{
	// TODO: Implement.
}

// To ZED conversion functions.

zed::view to_sennet(const sl::VIEW& x)
{
	switch (x)
	{
		case sl::VIEW::LEFT:
			return zed::view::left;
		case sl::VIEW::RIGHT:
			return zed::view::right;
		case sl::VIEW::LEFT_GRAY:
			return zed::view::left_gray;
		case sl::VIEW::RIGHT_GRAY:
			return zed::view::right_gray;
		case sl::VIEW::LEFT_UNRECTIFIED:
			return zed::view::left_unrectified;
		case sl::VIEW::RIGHT_UNRECTIFIED:
			return zed::view::right_unrectified;
		case sl::VIEW::LEFT_UNRECTIFIED_GRAY:
			return zed::view::left_unrectified_gray;
		case sl::VIEW::RIGHT_UNRECTIFIED_GRAY:
			return zed::view::right_unrectified_gray;
		case sl::VIEW::SIDE_BY_SIDE:
			return zed::view::side_by_side;
		default:
			return zed::view::none;
	}
}

zed::resolution to_sennet(const sl::RESOLUTION& x)
{
	switch (x)
	{
		case sl::RESOLUTION::HD2K:
			return zed::resolution::hd2k;
		case sl::RESOLUTION::HD1080:
			return zed::resolution::hd1080;
		case sl::RESOLUTION::HD720:
			return zed::resolution::hd720;
		case sl::RESOLUTION::VGA:
			return zed::resolution::vga;
		default:
			return zed::resolution::none;
	}
}

zed::video_settings to_sennet(const sl::VIDEO_SETTINGS& x)
{
	switch (x)
	{
		case sl::VIDEO_SETTINGS::BRIGHTNESS:
			return zed::video_settings::brightness;
		case sl::VIDEO_SETTINGS::CONTRAST:
			return zed::video_settings::contrast;
		case sl::VIDEO_SETTINGS::HUE:
			return zed::video_settings::hue;
		case sl::VIDEO_SETTINGS::SATURATION:
			return zed::video_settings::saturation;
		case sl::VIDEO_SETTINGS::SHARPNESS:
			return zed::video_settings::sharpness;
		case sl::VIDEO_SETTINGS::GAIN:
			return zed::video_settings::gain;
		case sl::VIDEO_SETTINGS::EXPOSURE:
			return zed::video_settings::exposure;
		case sl::VIDEO_SETTINGS::AEC_AGC:
			return zed::video_settings::aec_agc;
		case sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE:
			return zed::video_settings::whitebalance_temperature;
		case sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO:
			return zed::video_settings::whitebalance_auto;
		case sl::VIDEO_SETTINGS::LED_STATUS:
			return zed::video_settings::led_status;
		default:
			return zed::video_settings::none;
	}
}

zed::depth_mode to_sennet(const sl::DEPTH_MODE& x)
{
	switch (x)
	{
		case sl::DEPTH_MODE::PERFORMANCE:
			return zed::depth_mode::performance;
		case sl::DEPTH_MODE::QUALITY:
			return zed::depth_mode::quality;
		case sl::DEPTH_MODE::ULTRA:
			return zed::depth_mode::ultra;
		default:
			return zed::depth_mode::none;
	}
}

zed::unit to_sennet(const sl::UNIT& x)
{
	switch (x)
	{
		case sl::UNIT::MILLIMETER:
			return zed::unit::millimeter;		
		case sl::UNIT::CENTIMETER:
			return zed::unit::centimeter;
		case sl::UNIT::METER:
			return zed::unit::meter;
		case sl::UNIT::INCH:
			return zed::unit::inch;
		case sl::UNIT::FOOT:
			return zed::unit::foot;
		default:
			return zed::unit::none;
	}
}

zed::svo_compression_mode to_sennet(const sl::SVO_COMPRESSION_MODE& x)
{
	switch (x)
	{
		case sl::SVO_COMPRESSION_MODE::LOSSLESS:
			return zed::svo_compression_mode::lossless;
		case sl::SVO_COMPRESSION_MODE::H264:
			return zed::svo_compression_mode::h264;
		case sl::SVO_COMPRESSION_MODE::H265:
			return zed::svo_compression_mode::h265;
		default:
			return zed::svo_compression_mode::none;
	}
}

zed::sensing_mode to_sennet(const sl::SENSING_MODE& x)
{
	switch (x)
	{
		case sl::SENSING_MODE::STANDARD:
			return zed::sensing_mode::standard;
		case sl::SENSING_MODE::FILL:
			return zed::sensing_mode::fill;
		default:
			return zed::sensing_mode::none;
	}
}

zed::reference_frame to_sennet(const sl::REFERENCE_FRAME& x)
{
	switch (x)
	{
		case sl::REFERENCE_FRAME::WORLD:
			return zed::reference_frame::world;		
		case sl::REFERENCE_FRAME::CAMERA:
			return zed::reference_frame::camera;
		default:
			return zed::reference_frame::none;
	}
}

std::shared_ptr<zed::image> to_sennet(const sl::Mat& m)
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
	return std::make_shared<zed::image>(m.getPtr<unsigned char>(),
		m.getWidth(), m.getHeight(), m.getChannels());
}

zed::init_params to_sennet(const sl::InitParameters& x)
{
	// TODO: Implement.
}

zed::recording_params to_sennet(const sl::RecordingParameters& x)
{
	// TODO: Implement.
}

zed::runtime_params to_sennet(const sl::RuntimeParameters& x)
{
	// TODO: Implement.
}

};

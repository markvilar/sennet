#include <Sennet/Primitives/ZEDParameters.hpp>

namespace Sennet
{

namespace ZED
{

InitParameters::InitParameters(
	const depth_mode mode,
	const unit coord_units,
	const coordinate_system coord_sys,
	const int depth_stab,
	const float depth_min,
	const float depth_max,
	const bool depth_right,
	const resolution resolution,
	const int camera_fps,
	const bool img_enhancement,
	const bool disable_self_calib,
	const bool sdk_verbose,
	const bool sensors_required
	)
	: m_depth_mode(mode), m_coord_units(coord_units), 
	m_coord_sys(coord_sys), m_depth_stab(depth_stab),
	m_depth_min(depth_min), m_depth_max(depth_max),
	m_depth_right(depth_right), m_resolution(resolution),
	m_camera_fps(camera_fps), m_img_enhancement(img_enhancement),
	m_disable_self_calib(disable_self_calib), m_sdk_verbose(sdk_verbose),
	m_sensors_required(sensors_required)
{
	// TODO: Add assertions?
}

std::string InitParameters::ToString() const
{
	std::stringstream ss;
	ss << "[InitParameters] \n" 
		<< "mode: " << ::ToString(get_depth_mode()) << ", "
		<< "unit: " << ::ToString(get_coord_units()) << ", "
		<< "sys.: " << ::ToString(get_coord_sys()) << ", "
		<< "stab.: " << get_depth_stab() << ", "
		<< "min. depth: " << get_min_depth() << ", "
		<< "max. depth: " << get_max_depth() << ", "
		<< "depth right: " << std::boolalpha << right_depth_enabled()
		<< "\nres.: " << ::ToString(get_resolution()) << ", "
		<< "fps: " << get_camera_fps() << ", "
		<< "img. enh.: " << std::boolalpha 
		<< img_enhance_enabled() << ", "
		<< "disable self calib.: " << std::boolalpha 
		<< self_calib_disabled() << ", "
		<< "sdk verbose: " << std::boolalpha 
		<< is_sdk_verbose() << ", "
		<< "sensors req.: " << std::boolalpha
		<< sensors_required();
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const InitParameters& ip)
{
	return os << ip.ToString();
}

RecordingParameters::RecordingParameters(
	const std::string filename,
	const svo_compression_mode comp_mode,
	const unsigned int target_bit_rate,
	const unsigned int target_frame_rate
	)
	: m_filename(filename), m_compression_mode(comp_mode), 
	m_target_bit_rate(target_bit_rate), 
	m_target_frame_rate(target_frame_rate)
{
	// TODO: Add assertions?
}

std::string RecordingParameters::ToString() const
{
	std::stringstream ss;
	ss << "[RecordingParameters] "
		<< "file: " << get_filename() << ", "
		<< "compr. mode: " << ::ToString(get_compression_mode()) << ", "
		<< "target bit rate: " << get_bit_rate() << ", "
		<< "target frame rate: " << get_frame_rate();
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const RecordingParameters& rp)
{
	return os << rp.ToString();
}

RuntimeParameters::RuntimeParameters(
	const sensing_mode mode,
	const reference_frame ref_frame,
	const bool depth_enabled,
	const int conf_threshold,
	const int text_conf_threshold
	)
	: m_sensing_mode(mode), m_ref_frame(ref_frame), 
	m_depth_enabled(depth_enabled), m_conf_threshold(conf_threshold),
	m_text_conf_threshold(text_conf_threshold)
{
	// TODO: Add assertions?
}

std::string RuntimeParameters::ToString() const
{
	std::stringstream ss;
	ss << "[RuntimeParameters] "
		<< "sensing mode: " << ::ToString(get_sensing_mode()) << ", "
		<< "ref. frame: " << ::ToString(get_reference_frame()) << ", "
		<< "depth enabled: " << std::boolalpha 
		<< is_depth_enabled() << ", "
		<< "conf. thres.: " << get_confidence_threshold() << ", "
		<< "text. conf. thres.: " << get_texture_confidence_threshold();
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const RuntimeParameters& rp)
{
	return os << rp.ToString();
}

}
}



std::string ToString(const Sennet::ZED::coordinate_system sys)
{
	switch (sys)
	{
		case Sennet::ZED::coordinate_system::image: 
			return std::string("image");
		case Sennet::ZED::coordinate_system::left_handed_y_up: 
			return std::string("left_handed_y_up");
		case Sennet::ZED::coordinate_system::right_handed_y_up:
			return std::string("right_handed_y_up");
		case Sennet::ZED::coordinate_system::right_handed_z_up:
			return std::string("right_handed_z_up");
		case Sennet::ZED::coordinate_system::left_handed_z_up:
			return std::string("left_handed_z_up");
		case Sennet::ZED::coordinate_system::right_handed_z_up_x_fwd:
			return std::string("right_handed_z_up_x_fwd");
		default: 
			return std::string("none");
	}
}

std::string ToString(const Sennet::ZED::depth_mode mode)
{
	switch (mode)
	{
		case Sennet::ZED::depth_mode::performance:
			return std::string("performance");
		case Sennet::ZED::depth_mode::quality:
			return std::string("quality");
		case Sennet::ZED::depth_mode::ultra:
			return std::string("ultra");
		default:
			return std::string("none");
	}
}

std::string ToString(const Sennet::ZED::reference_frame ref)
{
	switch (ref)
	{
		case Sennet::ZED::reference_frame::world:
			return std::string("world");
		case Sennet::ZED::reference_frame::camera:
			return std::string("camera");
		default:
			return std::string("none");
	}
}

std::string ToString(const Sennet::ZED::resolution res)
{
	switch (res)
	{
		case Sennet::ZED::resolution::hd2k:
			return std::string("hd2k");
		case Sennet::ZED::resolution::hd1080:
			return std::string("hd1080");
		case Sennet::ZED::resolution::hd720:
			return std::string("hd720");
		case Sennet::ZED::resolution::vga:
			return std::string("vga");
		default:
			return std::string("none");
	}
}

std::string ToString(const Sennet::ZED::svo_compression_mode scm)
{
	switch (scm)
	{
		case Sennet::ZED::svo_compression_mode::lossless:
			return std::string("lossless");
		case Sennet::ZED::svo_compression_mode::h264:
			return std::string("h264");
		case Sennet::ZED::svo_compression_mode::h265:
			return std::string("h265");
		default:
			return std::string("none");
	}
}

std::string ToString(const Sennet::ZED::sensing_mode sm)
{
	switch (sm)
	{
		case Sennet::ZED::sensing_mode::standard:
			return std::string("standard");
		case Sennet::ZED::sensing_mode::fill:
			return std::string("fill");
		default:
			return std::string("none");
	}
}

std::string ToString(const Sennet::ZED::unit u)
{
	switch (u)
	{
		case Sennet::ZED::unit::millimeter:
			return std::string("millimeter");
		case Sennet::ZED::unit::centimeter:
			return std::string("centimeter");
		case Sennet::ZED::unit::meter:
			return std::string("meter");
		case Sennet::ZED::unit::inch:
			return std::string("inch");
		case Sennet::ZED::unit::foot:
			return std::string("foot");
		default:
			return std::string("none");
	}
}

std::string ToString(const Sennet::ZED::video_settings vs)
{
	switch (vs)
	{
		case Sennet::ZED::video_settings::brightness:
			return std::string("brightness");
		case Sennet::ZED::video_settings::contrast:
			return std::string("contrast");
		case Sennet::ZED::video_settings::hue:
			return std::string("hue");
		case Sennet::ZED::video_settings::saturation:
			return std::string("saturation");
		case Sennet::ZED::video_settings::sharpness:
			return std::string("sharpness");
		case Sennet::ZED::video_settings::gain:
			return std::string("gain");
		case Sennet::ZED::video_settings::exposure:
			return std::string("exposure");
		case Sennet::ZED::video_settings::aec_agc:
			return std::string("aec_agc");
		case Sennet::ZED::video_settings::whitebalance_temperature:
			return std::string("whitebalance_temperature");
		case Sennet::ZED::video_settings::whitebalance_auto:
			return std::string("whitebalance_auto");
		case Sennet::ZED::video_settings::led_status:
			return std::string("led_status");
		default:
			return std::string("none");
	}
}

std::string ToString(const Sennet::ZED::view v)
{
	switch (v)
	{
		case Sennet::ZED::view::left:
			return std::string("left");
		case Sennet::ZED::view::right:
			return std::string("right");
		case Sennet::ZED::view::left_gray:
			return std::string("left_gray");
		case Sennet::ZED::view::right_gray:
			return std::string("right_gray");
		case Sennet::ZED::view::left_unrectified:
			return std::string("left_unrectified");
		case Sennet::ZED::view::right_unrectified:
			return std::string("right_unrectified");
		case Sennet::ZED::view::left_unrectified_gray:
			return std::string("left_unrectified_gray");
		case Sennet::ZED::view::right_unrectified_gray:
			return std::string("right_unrectified_gray");
		case Sennet::ZED::view::side_by_side:
			return std::string("side_by_side");
		default:
			return std::string("none");
	}
}

std::ostream& operator<<(
	std::ostream& os, 
	const Sennet::ZED::coordinate_system sys
	)
{
	return os << ToString(sys);
}

std::ostream& operator<<(
	std::ostream& os, 
	const Sennet::ZED::depth_mode mode
	)
{
	return os << ToString(mode);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::reference_frame ref)
{
	return os << ToString(ref);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::resolution res)
{
	return os << ToString(res);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::svo_compression_mode scm)
{
	return os << ToString(scm);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::sensing_mode sm)
{
	return os << ToString(sm);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::unit u)
{
	return os << ToString(u);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::video_settings vs)
{
	return os << ToString(vs);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::view v)
{
	return os << ToString(v);
}

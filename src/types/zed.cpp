#include <sennet/types/zed.hpp>

namespace sennet
{

namespace zed
{

depth_init_params::depth_init_params(
		const depth_mode mode,
		const unit coord_units,
		const coordinate_system coord_sys,
		const int depth_stab,
		const float depth_min,
		const float depth_max,
		const bool depth_right
	)
	: m_depth_mode(mode), m_coord_units(coord_units), 
	m_coord_sys(coord_sys), m_depth_stab(depth_stab),
	m_depth_min(depth_min), m_depth_max(depth_max),
	m_depth_right(depth_right)
{
	// TODO: Add assertions?
}

std::string depth_init_params::to_string() const
{
	std::stringstream ss;
	ss << "[depth_init_params] " 
		<< "mode: " << ::to_string(get_depth_mode()) << ", "
		<< "unit: " << ::to_string(get_coord_units()) << ", "
		<< "sys.: " << ::to_string(get_coord_sys()) << ", "
		<< "stab.: " << get_depth_stab() << ", "
		<< "min. depth: " << get_min_depth() << ", "
		<< "max. depth: " << get_max_depth() << ", "
		<< "depth right: " << std::boolalpha << right_depth_enabled();
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, 
		const depth_init_params& dp)
{
	os << dp.to_string();
	return os;
}



image::image()
	: m_buffer(),
	m_width(0),
	m_height(0),
	m_channels(0)
{
}

image::image(const unsigned char* ptr, const size_t width, const size_t height,
	const size_t channels)
{
	m_buffer.assign(ptr, ptr + width*height*channels);
	m_width = width;
	m_height = height;
	m_channels = channels;
}

image::image(const image& other)
	: m_buffer(other.get_buffer()),
	m_width(other.get_width()), 
	m_height(other.get_height()),
	m_channels(other.get_channels())
{
	// TODO: Debug this to make sure it copies correctly.
}

image::~image()
{
}

unsigned char image::get_pixel(const size_t col, const size_t row, 
	const size_t channel) const
{
	try
	{
		size_t width = get_width();
		size_t height = get_height();
		size_t channels = get_channels();
		if (col >= width)
		{
			throw std::out_of_range("sennet::zed::image : "
				"width of out range");
		}
		else if (row >= height)
		{
			throw std::out_of_range("sennet::zed::image : "
				"heigth of out range");
		}
		else if (channel >= channels)
		{
			throw std::out_of_range("sennet::zed::image : "
				"channel of out range");
		}
		else
		{
			return m_buffer[col*channels+row*width*channels+channel];
		}
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << oor.what() << "\n";
		return 0;
	}
}

void image::set_pixel(const size_t col, const size_t row, 
	const size_t channel, const unsigned char value)
{
	try
	{
		size_t width = get_width();
		size_t height = get_height();
		size_t channels = get_channels();
		if (col >= width)
		{
			throw std::out_of_range("sennet::zed::image : "
				"width of out range");
		}
		else if (row >= height)
		{
			throw std::out_of_range("sennet::zed::image : "
				"heigth of out range");
		}
		else if (channel >= channels)
		{
			throw std::out_of_range("sennet::zed::image : "
				"channel of out range");
		}
		else
		{
			m_buffer[col*channels+row*width*channels+channel] = 
				value;
		}
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << oor.what() << "\n";
	}
}

std::string image::to_string() const
{
	std::stringstream ss;
	ss << "[zed::image] " << static_cast<const void*>(get_ptr()) << ", (" 
		<< get_width() << "," << get_height() << "," << get_channels() 
		<< "), size: " << get_size();
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const image& img)
{
	os << img.to_string();
	return os;
}

init_params::init_params(
		const depth_init_params depth_params,
		const resolution resolution,
		const int camera_fps,
		const bool img_enhancement,
		const bool disable_self_calib,
		const bool sdk_verbose,
		const bool sensors_required
	)
	: m_depth_params(depth_params), m_resolution(resolution),
	m_camera_fps(camera_fps), m_img_enhancement(img_enhancement),
	m_disable_self_calib(disable_self_calib), m_sdk_verbose(sdk_verbose),
	m_sensors_required(sensors_required)
{
	// TODO: Add assertions?
}

std::string init_params::to_string() const
{
	std::stringstream ss;
	ss << "[init_params]" << get_depth_params().to_string() << "\n" 
		<< "[init_params] "
		<< "res.: " << ::to_string(get_resolution()) << ", "
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

std::ostream& operator<<(std::ostream& os, const init_params& ip)
{
	os << ip.to_string();
	return os;
}

recording_params::recording_params(
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

std::string recording_params::to_string() const
{
	std::stringstream ss;
	ss << "[recording_params] "
		<< "file: " << get_filename() << ", "
		<< "compr. mode: " << ::to_string(get_compression_mode()) << ", "
		<< "target bit rate: " << get_bit_rate() << ", "
		<< "target frame rate: " << get_frame_rate();
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const recording_params& rp)
{
	os << rp.to_string();
	return os;
}

runtime_params::runtime_params(
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

std::string runtime_params::to_string() const
{
	std::stringstream ss;
	ss << "[runtime_params] "
		<< "sensing mode: " << ::to_string(get_sensing_mode()) << ", "
		<< "ref. frame: " << ::to_string(get_reference_frame()) << ", "
		<< "depth enabled: " << std::boolalpha 
		<< is_depth_enabled() << ", "
		<< "conf. thres.: " << get_confidence_threshold() << ", "
		<< "text. conf. thres.: " << get_texture_confidence_threshold();
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const runtime_params& rp)
{
	os << rp.to_string();
	return os;
}

}
};



std::string to_string(const sennet::zed::coordinate_system sys)
{
	switch (sys)
	{
		case sennet::zed::coordinate_system::image: 
			return std::string("image");
		case sennet::zed::coordinate_system::left_handed_y_up: 
			return std::string("left_handed_y_up");
		case sennet::zed::coordinate_system::right_handed_y_up:
			return std::string("right_handed_y_up");
		case sennet::zed::coordinate_system::right_handed_z_up:
			return std::string("right_handed_z_up");
		case sennet::zed::coordinate_system::left_handed_z_up:
			return std::string("left_handed_z_up");
		case sennet::zed::coordinate_system::right_handed_z_up_x_fwd:
			return std::string("right_handed_z_up_x_fwd");
		default: 
			return std::string("none");
	}
}

std::string to_string(const sennet::zed::depth_mode mode)
{
	switch (mode)
	{
		case sennet::zed::depth_mode::performance:
			return std::string("performance");
		case sennet::zed::depth_mode::quality:
			return std::string("quality");
		case sennet::zed::depth_mode::ultra:
			return std::string("ultra");
		default:
			return std::string("none");
	}
}

std::string to_string(const sennet::zed::reference_frame ref)
{
	switch (ref)
	{
		case sennet::zed::reference_frame::world:
			return std::string("world");
		case sennet::zed::reference_frame::camera:
			return std::string("camera");
		default:
			return std::string("none");
	}
}

std::string to_string(const sennet::zed::resolution res)
{
	switch (res)
	{
		case sennet::zed::resolution::hd2k:
			return std::string("hd2k");
		case sennet::zed::resolution::hd1080:
			return std::string("hd1080");
		case sennet::zed::resolution::hd720:
			return std::string("hd720");
		case sennet::zed::resolution::vga:
			return std::string("vga");
		default:
			return std::string("none");
	}
}

std::string to_string(const sennet::zed::svo_compression_mode scm)
{
	switch (scm)
	{
		case sennet::zed::svo_compression_mode::lossless:
			return std::string("lossless");
		case sennet::zed::svo_compression_mode::h264:
			return std::string("h264");
		case sennet::zed::svo_compression_mode::h265:
			return std::string("h265");
		default:
			return std::string("none");
	}
}

std::string to_string(const sennet::zed::sensing_mode sm)
{
	switch (sm)
	{
		case sennet::zed::sensing_mode::standard:
			return std::string("standard");
		case sennet::zed::sensing_mode::fill:
			return std::string("fill");
		default:
			return std::string("none");
	}
}

std::string to_string(const sennet::zed::unit u)
{
	switch (u)
	{
		case sennet::zed::unit::millimeter:
			return std::string("millimeter");
		case sennet::zed::unit::centimeter:
			return std::string("centimeter");
		case sennet::zed::unit::meter:
			return std::string("meter");
		case sennet::zed::unit::inch:
			return std::string("inch");
		case sennet::zed::unit::foot:
			return std::string("foot");
		default:
			return std::string("none");
	}
}

std::string to_string(const sennet::zed::video_settings vs)
{
	switch (vs)
	{
		case sennet::zed::video_settings::brightness:
			return std::string("brightness");
		case sennet::zed::video_settings::contrast:
			return std::string("contrast");
		case sennet::zed::video_settings::hue:
			return std::string("hue");
		case sennet::zed::video_settings::saturation:
			return std::string("saturation");
		case sennet::zed::video_settings::sharpness:
			return std::string("sharpness");
		case sennet::zed::video_settings::gain:
			return std::string("gain");
		case sennet::zed::video_settings::exposure:
			return std::string("exposure");
		case sennet::zed::video_settings::aec_agc:
			return std::string("aec_agc");
		case sennet::zed::video_settings::whitebalance_temperature:
			return std::string("whitebalance_temperature");
		case sennet::zed::video_settings::whitebalance_auto:
			return std::string("whitebalance_auto");
		case sennet::zed::video_settings::led_status:
			return std::string("led_status");
		default:
			return std::string("none");
	}
}

std::string to_string(const sennet::zed::view v)
{
	switch (v)
	{
		case sennet::zed::view::left:
			return std::string("left");
		case sennet::zed::view::right:
			return std::string("right");
		case sennet::zed::view::left_gray:
			return std::string("left_gray");
		case sennet::zed::view::right_gray:
			return std::string("right_gray");
		case sennet::zed::view::left_unrectified:
			return std::string("left_unrectified");
		case sennet::zed::view::right_unrectified:
			return std::string("right_unrectified");
		case sennet::zed::view::left_unrectified_gray:
			return std::string("left_unrectified_gray");
		case sennet::zed::view::right_unrectified_gray:
			return std::string("right_unrectified_gray");
		case sennet::zed::view::side_by_side:
			return std::string("side_by_side");
		default:
			return std::string("none");
	}
}

std::ostream& operator<<(
	std::ostream& os, 
	const sennet::zed::coordinate_system sys
	)
{
	os << to_string(sys);
	return os;
}

std::ostream& operator<<(
	std::ostream& os, 
	const sennet::zed::depth_mode mode
	)
{
	os << to_string(mode);
	return os;
}

std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::reference_frame ref)
{
	os << to_string(ref);
	return os;
}

std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::resolution res)
{
	os << to_string(res);
	return os;
}

std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::svo_compression_mode scm)
{
	os << to_string(scm);
	return os;
}

std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::sensing_mode sm)
{
	os << to_string(sm);
	return os;
}

std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::unit u)
{
	os << to_string(u);
	return os;
}

std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::video_settings vs)
{
	os << to_string(vs);
	return os;
}

std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::view v)
{
	os << to_string(v);
	return os;
}

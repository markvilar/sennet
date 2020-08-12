#pragma once

#include <serializer/serializer.h>

namespace Sennet
{

namespace ZED
{

enum class coordinate_system
{
	none = 0, image, left_handed_y_up, right_handed_y_up, right_handed_z_up,
	left_handed_z_up, right_handed_z_up_x_fwd
};

enum class depth_mode 
{ 
	none = 0, performance, quality, ultra
};


enum class reference_frame 
{ 
	none = 0, world, camera 
};

enum class resolution 
{ 
	none = 0, hd2k, hd1080, hd720, vga 
};

enum class svo_compression_mode
{ 
	none = 0, lossless, h264, h265 
};

enum class sensing_mode 
{ 
	none = 0, standard, fill 
};

enum class unit 
{ 
	none = 0, millimeter, centimeter, meter, inch, foot 
};

enum class video_settings
{ 
	none = 0, brightness, contrast, hue, saturation, sharpness, gain, 
	exposure, aec_agc, whitebalance_temperature, whitebalance_auto,
	led_status
};

enum class view 
{ 
	none = 0, left, right, left_gray, right_gray, left_unrectified,
	right_unrectified, left_unrectified_gray, right_unrectified_gray,
	side_by_side
};

class InitParameters
{
	// Wrapper for sl::InitParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	InitParameters(
		const depth_mode mode=depth_mode::ultra,
		const unit coord_units=unit::millimeter,
		const coordinate_system coord_sys=coordinate_system::image,
		const int depth_stab=1,
		const float depth_min=-1,
		const float depth_max=-1,
		const bool depth_right=false,
		const resolution resolution=resolution::hd720,
		const int camera_fps=0,
		const bool img_enhancement=true,
		const bool disable_self_calib=false,
		const bool sdk_verbose=false,
		const bool sensors_required=false
	);
	~InitParameters() = default;

	// Depth functions.
	inline depth_mode get_depth_mode() const { return m_depth_mode; }
	inline unit get_coord_units() const { return m_coord_units; }
	inline coordinate_system get_coord_sys() const { return m_coord_sys; }
	inline int get_depth_stab() const { return m_depth_stab; }
	inline float get_min_depth() const { return m_depth_min; }
	inline float get_max_depth() const { return m_depth_max; }
	inline bool right_depth_enabled() const { return m_depth_right; }

	// Generic functions.
	inline resolution get_resolution() const { return m_resolution; }
	inline int get_camera_fps() const { return m_camera_fps; }
	inline bool img_enhance_enabled() const { return m_img_enhancement; }
	inline bool self_calib_disabled() const { return m_disable_self_calib; }
	inline bool is_sdk_verbose() const { return m_sdk_verbose; }
	inline bool sensors_required() const { return m_sensors_required; }

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, const InitParameters& ip);

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_depth_mode);
		archive(self.m_coord_units);
		archive(self.m_coord_sys);
		archive(self.m_depth_stab);
		archive(self.m_depth_min);
		archive(self.m_depth_max);
		archive(self.m_depth_right);

		archive(self.m_resolution);
		archive(self.m_camera_fps);
		archive(self.m_img_enhancement);
		archive(self.m_disable_self_calib);
		archive(self.m_sdk_verbose);
		archive(self.m_sensors_required);
	}

private:
	// Depth related members.
	depth_mode m_depth_mode;
	unit m_coord_units;
	coordinate_system m_coord_sys;
	int m_depth_stab;
	float m_depth_min;
	float m_depth_max;
	bool m_depth_right;

	// Generic members.
	resolution m_resolution;
	int m_camera_fps;
	bool m_img_enhancement;
	bool m_disable_self_calib;
	bool m_sdk_verbose;
	bool m_sensors_required;
};

class RecordingParameters
{
	// Wrapper for sl::RecordingParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	RecordingParameters(
		const std::string filename="myRecording.svo", 
		const svo_compression_mode comp_mode=svo_compression_mode::h264,
		const unsigned int target_bit_rate=0,
		const unsigned int target_frame_rate=0
		);

	inline std::string get_filename() const { return m_filename; }
	inline svo_compression_mode get_compression_mode() const
	{
		return m_compression_mode;
	}
	inline unsigned int get_bit_rate() const { return m_target_bit_rate; }
	inline unsigned int get_frame_rate() const 
	{ 
		return m_target_frame_rate; 
	}

	// TODO: Implement set functions?

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, 
		const RecordingParameters& rp);

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_filename);
		archive(self.m_compression_mode);
		archive(self.m_target_bit_rate);
		archive(self.m_target_frame_rate);
	}

private:
	std::string m_filename;
	svo_compression_mode m_compression_mode;
	unsigned int m_target_bit_rate;
	unsigned int m_target_frame_rate;
};

class RuntimeParameters
{
	// Wrapper for sl::RuntimeParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	RuntimeParameters(
		const sensing_mode mode=sensing_mode::standard,
		const reference_frame ref_frame=reference_frame::camera,
		const bool depth_enabled=true,
		const int conf_threshold=100,
		const int text_conf_threshold=100
		);

	inline sensing_mode get_sensing_mode() const { return m_sensing_mode; }
	inline reference_frame get_reference_frame() const { return m_ref_frame; }
	inline bool is_depth_enabled() const { return m_depth_enabled; }
	inline int get_confidence_threshold() const 
	{ 
		return m_conf_threshold; 
	}
	inline int get_texture_confidence_threshold() const 
	{ return m_text_conf_threshold;
	}

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, 
		const RuntimeParameters& rp);

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_sensing_mode);
		archive(self.m_ref_frame);
		archive(self.m_depth_enabled);
		archive(self.m_conf_threshold);
		archive(self.m_text_conf_threshold);
	}


private:
	sensing_mode m_sensing_mode;
	reference_frame m_ref_frame;
	bool m_depth_enabled;
	int m_conf_threshold;
	int m_text_conf_threshold;
};

}
}

std::string ToString(const Sennet::ZED::coordinate_system sys);
std::string ToString(const Sennet::ZED::depth_mode mode);
std::string ToString(const Sennet::ZED::reference_frame ref);
std::string ToString(const Sennet::ZED::resolution res);
std::string ToString(const Sennet::ZED::svo_compression_mode scm);
std::string ToString(const Sennet::ZED::sensing_mode sm);
std::string ToString(const Sennet::ZED::unit u);
std::string ToString(const Sennet::ZED::video_settings vs);
std::string ToString(const Sennet::ZED::view v);

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::coordinate_system sys);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::depth_mode mode);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::reference_frame ref);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::resolution res);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::svo_compression_mode scm);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::sensing_mode sm);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::unit u);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::video_settings vs);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::view v);

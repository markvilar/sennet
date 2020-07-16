#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>

namespace sennet
{

namespace zed
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

class depth_init_params
{
	// Encapsulate of the parameters in sl::InitParameters related to depth
	// measurement and the depth map computed by the ZED. 
public:
	depth_init_params(
		const depth_mode mode=depth_mode::ultra,
		const unit coord_units=unit::millimeter,
		const coordinate_system coord_sys=coordinate_system::image,
		const int depth_stab=1,
		const float depth_min=-1,
		const float depth_max=-1,
		const bool depth_right=false
	);
	~depth_init_params() = default;

	inline depth_mode get_depth_mode() const { return m_depth_mode; }
	inline unit get_coord_units() const { return m_coord_units; }
	inline coordinate_system get_coord_sys() const { return m_coord_sys; }
	inline int get_depth_stab() const { return m_depth_stab; }
	inline float get_min_depth() const { return m_depth_min; }
	inline float get_max_depth() const { return m_depth_max; }
	inline bool right_depth_enabled() const { return m_depth_right; }

	// TODO: Implement set functions?

	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream& os, 
		const depth_init_params& dp);

	friend class init_params;

private:
	depth_mode m_depth_mode;
	unit m_coord_units;
	coordinate_system m_coord_sys;
	int m_depth_stab;
	float m_depth_min;
	float m_depth_max;
	bool m_depth_right;
};

class image
{
	// Wrapper for sl::Mat with unsigned char data. Neglects functionality 
	// of the Stereolabs SDK that is considered unimportant for recording.
public:
	image();
	image(const unsigned char* ptr, const size_t width, const size_t height, 
		const size_t channels);
	image(const image& other);
	~image();

	inline std::vector<unsigned char> get_buffer() const { return m_buffer; }
	inline unsigned char* get_ptr() { return m_buffer.data(); }
	inline const unsigned char* get_ptr() const { return m_buffer.data(); }
	inline size_t get_width() const { return m_width; }
	inline size_t get_height() const { return m_height; }
	inline size_t get_channels() const { return m_channels; }
	inline size_t get_size() const { return m_width * m_height * m_channels; }

	unsigned char get_pixel(const size_t col, const size_t row, 
		const size_t channel) const;
	void set_pixel(const size_t col, const size_t row, 
		const size_t channel, const unsigned char value);
	void print_pixel(const size_t w, const size_t h) const;

	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream& os, const image& img);
	// TODO: Add reset, reshape and get pixel method.

private:

private:
	std::vector<unsigned char> m_buffer;
	size_t m_width;
	size_t m_height;
	size_t m_channels;
};

class init_params
{
	// Wrapper for sl::InitParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	init_params(
		const depth_init_params depth_params,
		const resolution resolution=resolution::hd720,
		const int camera_fps=0,
		const bool img_enhancement=true,
		const bool disable_self_calib=false,
		const bool sdk_verbose=false,
		const bool sensors_required=false
	);
	~init_params() = default;

	inline depth_init_params get_depth_params() const 
	{ 
		return m_depth_params; 
	}
	inline resolution get_resolution() const { return m_resolution; }
	inline int get_camera_fps() const { return m_camera_fps; }
	inline bool img_enhance_enabled() const { return m_img_enhancement; }
	inline bool self_calib_disabled() const { return m_disable_self_calib; }
	inline bool is_sdk_verbose() const { return m_sdk_verbose; }
	inline bool sensors_required() const { return m_sensors_required; }

	// TODO: Implement set functions?

	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream& os, const init_params& ip);

	// TODO: Add conversion function to sl::InitParameters in 
	// conversion/zed.

private:
	depth_init_params m_depth_params;
	resolution m_resolution;
	int m_camera_fps;
	bool m_img_enhancement;
	bool m_disable_self_calib;
	bool m_sdk_verbose;
	bool m_sensors_required;
};

class recording_params
{
	// Wrapper for sl::RecordingParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	recording_params(
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

	std::string to_string() const;
	friend std::ostream& operator<<(
		std::ostream& os, 
		const recording_params& rp
		);

private:
	std::string m_filename;
	svo_compression_mode m_compression_mode;
	unsigned int m_target_bit_rate;
	unsigned int m_target_frame_rate;
};

class runtime_params
{
	// Wrapper for sl::RuntimeParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	runtime_params(
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

	// TODO: Add set methods?

	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream& os, 
		const runtime_params& rp);

private:
	sensing_mode m_sensing_mode;
	reference_frame m_ref_frame;
	bool m_depth_enabled;
	int m_conf_threshold;
	int m_text_conf_threshold;
};



}
};

std::string to_string(const sennet::zed::coordinate_system sys);
std::string to_string(const sennet::zed::depth_mode mode);
std::string to_string(const sennet::zed::reference_frame ref);
std::string to_string(const sennet::zed::resolution res);
std::string to_string(const sennet::zed::svo_compression_mode scm);
std::string to_string(const sennet::zed::sensing_mode sm);
std::string to_string(const sennet::zed::unit u);
std::string to_string(const sennet::zed::video_settings vs);
std::string to_string(const sennet::zed::view v);

std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::coordinate_system sys);
std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::depth_mode mode);
std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::reference_frame ref);
std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::resolution res);
std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::svo_compression_mode scm);
std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::sensing_mode sm);
std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::unit u);
std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::video_settings vs);
std::ostream& operator<<(std::ostream& os, 
	const sennet::zed::view v);
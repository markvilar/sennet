#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>

namespace sennet
{

namespace zed
{

enum class view 
{ 
	none = 0, left, right, left_gray, right_gray, left_unrectified,
	right_unrectified, left_unrectified_gray, right_unrectified_gray,
	side_by_side
};

enum class resolution 
{ 
	none = 0, hd2k, hd1080, hd720, vga 
};

enum class video_settings
{ 
	none = 0, brightness, contrast, hue, saturation, sharpness, gain, 
	exposure, aec_agc, whitebalance_temperature, whitebalance_auto,
	led_status
};

enum class depth_mode 
{ 
	none = 0, performance, quality, ultra
};

enum class unit 
{ 
	none = 0, millimeter, centimeter, meter, inch, foot 
};

enum class svo_compression_mode
{ 
	none = 0, lossless, h264, h265 
};

enum class sensing_mode 
{ 
	none = 0, standard, fill 
};

enum class reference_frame 
{ 
	none = 0, world, camera 
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
	init_params();

private:
	resolution m_resolution;
	int m_fps;
	int m_image_flip;
	bool m_disable_self_calib;
	bool right_side_measure;
	depth_mode m_depth_mode;
	int m_depth_stab;
	float m_depth_min_dist;
	float m_depth_max_dist;
	unit m_unit;
	bool m_sdk_verbose;
	bool m_sensors_required;
	bool m_image_enhancement;
};

class recording_params
{
	// Wrapper for sl::RecordingParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	recording_params();

	inline std::string get_filename() const { return m_filename; }
	inline svo_compression_mode get_compression_mode() const
	{
		return m_compression_mode;
	}
	inline unsigned int get_bit_rate() const { return m_bit_rate; }
	inline unsigned int get_frame_rate() const { return m_frame_rate; }

private:
	std::string m_filename;
	svo_compression_mode m_compression_mode;
	unsigned int m_bit_rate;
	unsigned int m_frame_rate;
};

class runtime_params
{
	// Wrapper for sl::RuntimeParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	runtime_params();

	inline sensing_mode get_sensing_mode() const { return m_sensing_mode; }
	inline reference_frame get_reference_frame() const { return m_ref_frame; }
	inline bool get_enable_depth() const { return m_enable_depth; }
	inline int get_confidence_threshold() const 
	{ 
		return m_conf_threshold; 
	}
	inline int get_texture_confidence_threshold() const 
	{ 
		return m_text_conf_threshold;
	}


private:
	sensing_mode m_sensing_mode;
	reference_frame m_ref_frame;
	bool m_enable_depth;
	int m_conf_threshold;
	int m_text_conf_threshold;
};

};
};

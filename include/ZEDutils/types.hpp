#include <boost/cstdint.hpp>

#include <sl/Camera.hpp>

namespace zed { 

namespace net {

// Message types
enum class message : unsigned char 
{
	request,
	state,
	image,
	invalid
};

// Request types
enum class request : unsigned char
{	
	open,
	close,
	start_record,
	stop_record,
	set_brightness,
	set_contrast,
	set_hue,
	set_saturation,
	set_sharpness,
	set_gamma,
	set_gain,
	set_exposure,
	set_fps,
	set_resolution,
	set_root_dir,
	ping,
	invalid
};

// Image types
enum class image : unsigned char
{
	HD2K,
	HD1080,
	HD720,
	VGA
};

// States
enum class state : unsigned char
{
	open,
	closed,
	idle,
	busy,
	invalid
};

} // Namespace zed::net
}; // Namespace zed

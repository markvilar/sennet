#pragma once

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/requests/request.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_get_settings : public request
{
	typedef boost::asio::ip::tcp asio_tcp;
public:

	// Default constructor.
	zed_get_settings()
		: request()
	{
		// TODO: Initialize setting members.
	}

	// Copy constructor.
	zed_get_settings(const zed_get_settings& other)
		: request(other)
	{
		// TODO: Implement copying of setting members.
	}

	// Constructor.
	zed_get_settings(
		const std::string& sender_addr,
		const unsigned short sender_port
		)
		: request(sender_addr, sender_port)
	{
		// TODO: Initialize setting members.
	}
	
	// Constructor.
	zed_get_settings(const asio_tcp::endpoint& sender_ep)
		: request(sender_ep)
	{
		// TODO: Initialize setting members.
	}

	// Deconstructor.
	~zed_get_settings()
	{}

	// Action for runtime.
	void operator()(runtime& rt)
	{}

	// Action for zed_runtime.
	void operator()(zed_runtime& rt)
	{}

	base_action* clone() const
	{
		return new zed_get_settings(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
	}

private:
	// TODO: Add setting member.
	// sl::VIDEO_SETTINGS
	// BRIGHTNESS
	// CONTRAST
	// HUE
	// SATURATION
	// SHARPNESS
	// GAMMA
	// GAIN
	// EXPOSURE
	// AEC_AGC
	// AEC_AGC_ROI
	// WHITEBALANCE_TEMPERATURE
	// WHITEBALANCE_AUTO
	// LED_STATUS
	// LAST
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_get_settings,
	"am::action::zed_get_settings");

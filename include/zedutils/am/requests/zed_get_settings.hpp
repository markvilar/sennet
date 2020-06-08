#pragma once

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/requests/request.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_get_settings : public request
{
public:

	// Default constructor.
	zed_get_settings()
		: request()
	{}

	// Copy constructor.
	zed_get_settings(const zed_get_settings& other)
		: request(other)
	{
		// TODO: Implement.
	}

	// Constructor.
	zed_get_settings(
		const std::string& sender_addr,
		const unsigned short sender_port
		)
		: request(sender_addr, sender_port)
	{}
	

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
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_get_settings,
	"am::action::zed_get_settings");

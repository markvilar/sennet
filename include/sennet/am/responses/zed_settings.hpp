#pragma once

#include <algorithm>			// copy

#include <sl/Camera.hpp>

#include <sennet/am/core.hpp>
#include <sennet/am/responses/response.hpp>
#include <sennet/serialization.hpp>

namespace am { 
namespace action {

class zed_settings : public response
{
public:
	// Default constructor.
	zed_settings()
		: response()
	{}

	// Copy constructor.
	zed_settings(const zed_settings& other)
		: response(other)
	{
		// TODO: Verify that this works!
		std::copy(other.m_settings.begin(), other.m_settings.end(),
			back_inserter(m_settings));
	}

	// Constructor.
	zed_settings(
		const std::string& sender_addr,
		const unsigned short sender_port,
		const std::vector<sl::VIDEO_SETTINGS> settings
		)
		: response(sender_addr, sender_port)
	{
		// TODO: Verify that this works!
		std::copy(settings.begin(), settings.end(),
			back_inserter(m_settings));
	}

	// Destructor.
	~zed_settings()
	{}

	void operator()(runtime& rt)
	{
	}

	void operator()(zed_runtime& rt)
	{
	}

	base_action* clone() const
	{
		return new zed_settings(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<base_action>(*this);
		// TODO: Implement serialization function for 
		// std::vector<sl::VIDEO_SETTINGS>
		//ar & m_settings;
	}
private:
	std::vector<sl::VIDEO_SETTINGS> m_settings;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_settings,
	"am::action::zed_settings");

#pragma once

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_settings : public response
{
public:
	zed_settings()
	{
	}

	~zed_settings()
	{
	}

	void operator()(runtime& rt)
	{
	}

	void operator()(zed_runtime& rt)
	{
	}

	base_action* clone() const
	{
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<base_action>(*this);
	}
private:
	std::vector<sl::VIDEO_SETTINGS> m_settings;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_settings,
	"am::action::zed_settings");

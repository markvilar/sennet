#pragma once

#include <sl/Camera.hpp>

#include <zedutils/am/actions/request.hpp>
#include <zedutils/am/core.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_get_settings : public request
{
public:
	zed_get_settings()
	{
	}

	~zed_get_settings()
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
		ar & boost::serialization::base_object<request>(*this);
	}
private:
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_get_settings,
	"am::action::zed_get_settings");

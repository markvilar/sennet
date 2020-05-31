#pragma once

#include <string>

#include <sl/Camera.hpp>

#include <zedutils/am/actions/response.hpp>
#include <zedutils/am/core.hpp>
#include <zedutils/serialization.hpp>

namespace am { namespace action {

class zed_image : public response
{
public:
	zed_image()
	{
	}

	~zed_image()
	{
	}

	// Action for runtime.
	void operator()(runtime& rt)
	{
	}

	// Action for zed_runtime.
	void operator()(zed_runtime& rt)
	{
	}

	// Clones the object.
	base_action* clone() const
	{
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<base_action>(*this);
		ar & m_image;
		ar & m_view;
		ar & m_timestamp;
	}

private:
	sl::Mat m_image;
	sl::VIEW m_view;
	sl::Timestamp m_timestamp;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_image,
	"am::action::zed_image");

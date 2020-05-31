#pragma once

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>

namespace am { 
namespace action {

class zed_stop_record : public request
{
public:
	zed_stop_record()
	{
	}

	~zed_stop_record()
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

BOOST_CLASS_EXPORT_GUID(am::action::zed_stop_record,
	"am::action::zed_stop_record");

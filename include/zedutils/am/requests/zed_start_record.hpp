#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/requests/request.hpp>

namespace am { 
namespace action {

class zed_start_record : public request
{
public:
	zed_start_record()
	{
	}

	~zed_start_record()
	{
	}

	// Gets the recording parameters.
	sl::RecordingParameters get_rec_params() const { return m_rec_params; }

	// Sets the recording parameters.
	inline void set_rec_params(const sl::RecordingParameters& rec_params)
	{
		m_rec_params = rec_params;
	}

	void operator()(runtime& rt)
	{
	}

	void operator()(zed_runtime& rt)
	{
	}

	base_action* clone() const
	{
		// TODO: Implement.
		return new zed_start_record();
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
	}

private:
	sl::RecordingParameters m_rec_params;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_start_record,
	"am::action::zed_start_record");

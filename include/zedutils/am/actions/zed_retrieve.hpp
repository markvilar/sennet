#pragma once

#include <string>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/actions/request.hpp>
#include <zedutils/am/core.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_retrieve : public request
{
public:
	zed_retrieve()
	{
		// TODO: Implement.
	}

	~zed_retrieve()
	{
		// TODO: Implement.
	}

	// Gets the stereo view.
	sl::VIEW get_view() const { return m_view; }
	
	// Gets the runtime parameter.
	sl::RuntimeParameters get_run_params() const { return m_run_params; }

	// Sets the stereo view.
	inline void set_view(sl::VIEW& view) { m_view = view; }

	// Sets the runtime parameters.
	inline void set_runtime_params(sl::RuntimeParameters& run_params)
	{
		m_run_params = run_params;
	}

	// Action for runtime.
	void operator()(runtime& rt) override
	{
		std::cout << "This is a runtime. Cannot retrieve ZED image...\n";
	}

	// Action for zed_runtime.
	void operator()(zed_runtime& rt) override
	{
		std::cout << "This is a zed_runtime. "
			<< "Retrieving image from ZED...\n";
	}

	// Clones the object.
	base_action* clone() const override
	{
		// TODO: Implement proper copying.
		return new zed_retrieve();
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
		ar & m_run_params;
		ar & m_time_ref;
		ar & m_view;
	}

private:
	sl::RuntimeParameters m_run_params;
	sl::TIME_REFERENCE m_time_ref;
	sl::VIEW m_view;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_retrieve,
	"am::action::zed_retrieve");

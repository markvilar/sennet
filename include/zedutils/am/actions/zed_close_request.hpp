#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <zedutils/am/core.hpp>

namespace am { namespace action {

class zed_close_request : public base_action
{
private:
	
public:
	zed_close_request()
	{
	}

	~zed_close_request()
	{
	}

	// Action for base runtime instances.
	void operator()(runtime& rt)
	{
		std::cout << "This is a regular runtime. Cannot close zed...\n";
		// TODO: Implement sending of invalid request.
	}

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt)
	{
		std::cout << "This is a zed_runtime. Closing zed...\n";
		rt.close_zed();
	}

	// Clone function.
	base_action* clone() const
	{
		return new zed_close_request();
	}

	// Function for serializing with Boost.Serialization.
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<base_action>(*this);
	}
}; 

} // namespace action
}; // namespace am

BOOST_CLASS_EXPORT_GUID(am::action::zed_close_request,
	"am::action::zed_close_request");

#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <zedutils/am/actions/request.hpp>
#include <zedutils/am/core.hpp>

namespace am { 
namespace action {

class zed_close : public request
{
private:
	
public:
	zed_close()
	{
	}

	~zed_close()
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
		return new zed_close();
	}

	// Function for serializing with Boost.Serialization.
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
	}
}; 

} // namespace action
}; // namespace am

BOOST_CLASS_EXPORT_GUID(am::action::zed_close,
	"am::action::zed_close");

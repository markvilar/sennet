#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/requests/request.hpp>

namespace am { 
namespace action {

class zed_close : public request
{
private:
	
public:
	// Default constructor.
	zed_close() 
		: request()
	{}

	// Copy constructor.
	zed_close(const zed_close& other)
		: request(other)
	{
	}

	zed_close(
		const std::string sender_addr,
		const unsigned short sender_port
		)
		: request(sender_addr, sender_port)
	{}

	~zed_close()
	{
	}

	// Action for base runtime instances.
	void operator()(runtime& rt)
	{
		std::cout << "[AM] Cannot close zed...\n";
		// TODO: Implement sending of invalid request.
	}

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt)
	{
		std::cout << "[AM] Closing zed...\n";
		rt.close_zed();
	}

	// Clone function. TODO: Implement proper cloning.
	base_action* clone() const
	{
		return new zed_close(*this);
	}

	// Function for serializing with Boost.Serialization.
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
	}
}; 

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_close,
	"am::action::zed_close");

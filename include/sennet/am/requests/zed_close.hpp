#pragma once

#include <string>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sennet/am/core.hpp>
#include <sennet/am/requests/request.hpp>

namespace am { 
namespace action {

class zed_close : public request
{
	typedef boost::asio::ip::tcp asio_tcp;

public:
	// Default constructor.
	zed_close() 
		: request()
	{}

	// Copy constructor.
	zed_close(const zed_close& other)
		: request(other)
	{}

	// Constructor.
	zed_close(
		const std::string sender_addr,
		const unsigned short sender_port
		)
		: request(sender_addr, sender_port)
	{}

	// Constructor.
	zed_close(const asio_tcp::endpoint& sender_ep)
		: request(sender_ep)
	{}

	// Destructor.
	~zed_close()
	{}

	// Action for base runtime instances.
	void operator()(runtime& rt)
	{
		std::cout << "[AM] Cannot close zed...\n";
		// TODO: Implement sending of invalid request.
	}

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt)
	{
		if (rt.is_zed_opened() and rt.is_zed_recording())
		{
			std::cout << "[AM] ZED is recording. Not closing.\n";
		}
		else if (rt.is_zed_opened() and not rt.is_zed_recording())
		{
			rt.close_zed();
			std::cout << "[AM] Closed ZED.\n";
			// TODO: Implement sending of successful request.
		}
		else if (not rt.is_zed_opened())
		{
			std::cout << "[AM] ZED already close.\n";
		}
	}

	// Clone function.
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

private:
	
}; 

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_close,
	"am::action::zed_close");

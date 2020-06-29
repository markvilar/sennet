#pragma once

#include <string>

#include <sl/Camera.hpp>

#include <sennet/am/core.hpp>
#include <sennet/am/requests/request.hpp>

namespace am { 
namespace action {

class zed_stop_record : public request
{
	typedef boost::asio::ip::tcp asio_tcp;

public:
	// Default constructor.
	zed_stop_record()
		: request()
	{}

	// Copy constructor.
	zed_stop_record(const zed_stop_record& other)
		: request(other)
	{}

	// Constructor.
	zed_stop_record(
		const std::string sender_addr,
		const unsigned short sender_port
		)
		: request(sender_addr, sender_port)
	{}

	// Constructor.
	zed_stop_record(const asio_tcp::endpoint& sender_ep)
		: request(sender_ep)
	{}

	~zed_stop_record()
	{}

	void operator()(runtime& rt)
	{
	}

	void operator()(zed_runtime& rt)
	{
	}

	base_action* clone() const
	{
		return new zed_stop_record(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
	}

private:
	// TODO: Add members.
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_stop_record,
	"am::action::zed_stop_record");

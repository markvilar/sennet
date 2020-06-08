#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/requests/request.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class list_connections: public request
{

public:
	// Default constructor.
	list_connections()
		: request()
	{
	}

	// Copy constructor.
	list_connections(const list_connections& other)
		: request(other)
	{
	}

	// Constructor.
	list_connections(
		const std::string sender_addr,
		const unsigned short sender_port
		)
		: request(sender_addr, sender_port)
	{
	}

	// Destructor.
	~list_connections()
	{
	}

	void print_connections(runtime& rt)
	{
		auto conns = rt.get_connections();
		for (auto node : conns)
		{
			std::cout << "\n" << node.first.address().to_string()
				<< ":" << node.first.port() << "\n";
		}

		auto [addr, port] = get_sender();
		std::cout << "Sender: " << addr << ":" << port << "\n";
	}

	// Action for runtime instances.
	void operator()(runtime& rt)
	{
		print_connections(rt);
	}

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt)
	{
		print_connections(rt);
	}

	// Clone function.
	base_action* clone() const
	{
		return new list_connections(*this);
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

BOOST_CLASS_EXPORT_GUID(am::action::list_connections, 
	"am::action::list_connections");

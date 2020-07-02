#pragma once

#include <string>

#include <sennet/am/core.hpp>
#include <sennet/am/responses/response.hpp>

namespace am {
namespace action {

class message : public response
{
	typedef boost::asio::ip::tcp asio_tcp;

public:
	// Default constructor.
	message()
		: response()
	{}

	// Copy constructor.
	message(const message& other)
		: response(other)
	{
		m_msg = other.m_msg;
	}

	// Constructor.
	message(
		const std::string sender_addr,
		const unsigned short sender_port,
		const std::string msg
		)
		: response(sender_addr, sender_port),
		m_msg(msg)
	{}

	// Constructor.
	message(const asio_tcp::endpoint& sender_ep, const std::string msg)
		: response(sender_ep),
		m_msg(msg)
	{}

	// Destructor.
private:
	std::string m_msg;
};

}
};

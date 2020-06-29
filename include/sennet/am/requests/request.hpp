#pragma once

#include <string>
#include <tuple>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sennet/am/core.hpp>

namespace am { 
namespace action {

class request : public base_action
{
	typedef boost::asio::ip::tcp asio_tcp;
public:
	// Default constructor.
	request()
		: m_sender_addr(""),
		m_sender_port(0)
	{}

	// Copy constructor.
	request(const request& other)
	{
		m_sender_addr = other.m_sender_addr;
		m_sender_port = other.m_sender_port;
	}

	// Sender constructor.
	request(
		const std::string& sender_addr, 
		const unsigned short sender_port
		)
	{
		m_sender_addr = sender_addr;
		m_sender_port = sender_port;
	}

	request(const asio_tcp::endpoint& sender_ep)
	{
		m_sender_addr = sender_ep.address().to_string();
		m_sender_port = sender_ep.port();
	}

	// Virtual destructor due to this class being an interface.
	virtual ~request() {}

	// Gets the sender address and port.
	std::tuple<std::string, unsigned short> get_sender() const
	{
		return { m_sender_addr, m_sender_port };
	}

	// Checks if the given endpoint has the same address and port as the
	// sender.
	bool is_sender(const asio_tcp::endpoint& ep)
	{
		return (ep.address().to_string() == m_sender_addr) and
			(ep.port() == m_sender_port);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<base_action>(*this);
		ar & m_sender_addr;
		ar & m_sender_port;
	}

private:
	std::string m_sender_addr;
	unsigned short m_sender_port;
};

}
};

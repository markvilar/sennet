#pragma once

#include <string>
#include <tuple>

#include <zedutils/am/core.hpp>

namespace am { 
namespace action {

class request : public base_action
{
	typedef boost::asio::ip::tcp boost_tcp;
public:
	// Default constructor.
	request()
		: m_sender_addr("0.0.0.0"),
		m_sender_port(0),
		m_responder_addr("0.0.0.0"),
		m_responder_port(0),
		m_has_responder(false)
	{}

	// Copy constructor.
	request(const request& other)
	{
		m_sender_addr = other.m_sender_addr;
		m_sender_port = other.m_sender_port;
		m_responder_addr = other.m_responder_addr;
		m_responder_port = other.m_responder_port;
		m_has_responder = other.m_has_responder;
	}

	// Sender constructor.
	request(
		const std::string& sender_addr, 
		const unsigned short sender_port
		)
		: request()
	{
		m_sender_addr = sender_addr;
		m_sender_port = sender_port;
	}

	// Sender and responder constructor.
	request(
		const std::string& sender_addr, 
		const unsigned short sender_port,
		const std::string& responder_addr,
		const unsigned short responder_port
		)
		: request(sender_addr, sender_port)
	{
		m_responder_addr = responder_addr;
		m_responder_port = responder_port;
		m_has_responder = true;
	}

	// Virtual destructor due to this class being an interface.
	virtual ~request() {}

	// Gets the sender address and port.
	std::tuple<std::string, unsigned short> get_sender() const
	{
		return { m_sender_addr, m_sender_port };
	}

	// Gets the responder address and port.
	std::tuple<std::string, unsigned short> get_responder() const
	{
		return { m_responder_addr, m_responder_port };
	}

	// Checks if the request has a responder.
	bool has_responder() const { return m_has_responder; }

	// Sets the sender address and port.
	inline void set_sender(
		const std::string& addr, 
		const unsigned short port
		)
	{
		m_sender_addr = addr;
		m_sender_port = port;
	}

	// Sets the responder address and port.
	inline void set_responder(
		const std::string& addr,
		const unsigned short port
		)
	{
		m_responder_addr = addr;
		m_responder_port = port;
		m_has_responder = true;
	}

	// Checks if the given endpoint has the same address and port as the
	// sender.
	bool is_sender(const boost_tcp::endpoint& ep)
	{
		return (ep.address().to_string() == m_sender_addr) and
			(ep.port() == m_sender_port);
	}

	// Checks if the given endpoint has the same address and port as the
	// responder.
	bool is_responder(const boost_tcp::endpoint& ep)
	{
		return (ep.address().to_string() == m_responder_addr) and
			(ep.port() == m_responder_port);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<base_action>(*this);
		ar & m_sender_addr;
		ar & m_sender_port;
		ar & m_responder_addr;
		ar & m_responder_port;
		ar & m_has_responder;
	}

private:
	std::string m_sender_addr;
	unsigned short m_sender_port;
	std::string m_responder_addr;
	unsigned short m_responder_port;
	bool m_has_responder;
};

}
};

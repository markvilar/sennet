#pragma once

#include <zedutils/am/core.hpp>

namespace am {
namespace action {

class response : public base_action
{
	typedef boost::asio::ip::tcp boost_tcp;
public:
	// Default constructor.
	response() 
		: m_sender_addr(""),
		m_sender_port(0)
	{}

	// Copy constructor.
	response(const response& other)
	{
		m_sender_addr = other.m_sender_addr;
		m_sender_port = other.m_sender_port;
	}

	// Sender constructor.
	response(
		const std::string sender_addr, 
		const unsigned short sender_port
		)
	{
		m_sender_addr = sender_addr;
		m_sender_port = sender_port;
	}

	// Virtual destructor due to this class being an interface.
	virtual ~response() {}
	
	// Gets the sender address and port.
	std::tuple<std::string, unsigned short> get_sender() const
	{
		return { m_sender_addr, m_sender_port };
	}

	// Sets the sender address and port.
	inline void set_sender(
		const std::string addr, 
		const unsigned short port
		)
	{
		m_sender_addr = addr;
		m_sender_port = port;
	}

	// Checks if the given endpoint has the same address and port as the 
	// sender.
	bool is_sender(const boost_tcp::endpoint& ep)
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

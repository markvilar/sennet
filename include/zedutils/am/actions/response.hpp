#pragma once

#include <zedutils/am/core.hpp>

namespace am {
namespace action {

class response : public base_action
{
public:
	response() 
		: m_sender_addr(""),
		m_sender_port(0)
	{}

	response(boost::asio::ip::tcp::endpoint& sender)
	{
		m_sender_addr = sender.address().to_string();
		m_sender_port = sender.port();
	}

	// Virtual destructor due to this class being an interface.
	virtual ~response() {}
	
	// TODO: Implement get functions.

	inline void set_sender(
		const std::string addr, 
		const unsigned short port
		)
	{
		m_sender_addr = addr;
		m_sender_port = port;
	}

	inline void set_sender(boost::asio::ip::tcp::endpoint& sender)
	{
		set_sender(sender.address().to_string(), sender.port());
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

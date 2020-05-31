#pragma once

#include <zedutils/am/core.hpp>

namespace am { 
namespace action {

class request : public base_action
{
public:
	// TODO: Revise this class!
	request()
		: m_sender_addr(""),
		m_sender_port(0),
		m_responder_addr(""),
		m_responder_port(0),
		m_has_responder(false)
	{}

	request(const boost::asio::ip::tcp::endpoint& sender)
		: request()
	{
		m_sender_addr = sender.address().to_string();
		m_sender_port = sender.port();
	}
	
	request(
		const boost::asio::ip::tcp::endpoint& sender,
		const boost::asio::ip::tcp::endpoint& responder
		)
		: request(sender)
	{
		m_responder_addr = responder.address().to_string();
		m_responder_port = responder.port();
		m_has_responder = true;
	}

	// Virtual destructor due to this class being an interface.
	virtual ~request() {}

	// TODO: Implement get functions.

	inline void set_sender(
		const std::string addr, 
		const unsigned short port
		)
	{
		m_sender_addr = addr;
		m_sender_port = port;
	}

	inline void set_sender(const boost::asio::ip::tcp::endpoint& sender)
	{
		set_sender(sender.address().to_string(), sender.port());
	}

	inline void set_responder(
		const std::string addr,
		const unsigned short port
		)
	{
		m_responder_addr = addr;
		m_responder_port = port;
		m_has_responder = true;
	}

	inline void set_responder(
		const boost::asio::ip::tcp::endpoint& responder
		)
	{
		set_responder(responder.address().to_string(),
			responder.port());
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

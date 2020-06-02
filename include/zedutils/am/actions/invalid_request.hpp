#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <zedutils/am/actions/response.hpp>
#include <zedutils/am/core.hpp>

namespace am {
namespace action {

class invalid_request : public response
{
public:
	// Default constructor.
	invalid_request() 
		: response()
	{}

	// Copy constructor.
	invalid_request(const invalid_request& other)
		: response(other)
	{}

	// Constructor.
	invalid_request(
		const std::string sender_addr,
		const unsigned short sender_port,
		const std::string request_sender_addr,
		const unsigned short request_sender_port,
		const std::string request_type,
		const std::string message = ""
		)
		: response(sender_addr, sender_port)
	{
		m_request_sender_addr = request_sender_addr;
		m_request_sender_port = request_sender_port;
		m_request_type = request_type;
		m_message = message;
	}

	// Destructor.
	~invalid_request()
	{}

	// Prints the information of the invalid request.
	void print_to_console()
	{
		auto [receiver_addr, receiver_port] = get_sender();
		std::cout << "[INVALID REQUEST] "
			<< "Sender: " << m_request_sender_addr << ":" 
			<< m_request_sender_port << "\n"
			<< "Receiver: " << receiver_addr
			<< receiver_port << "\n"
			<< " - request type: " << m_request_type << "\n";
		if (!m_message.compare(""))
		{
			std::cout << " - message: " << m_message << "\n";
		}
	}

	// Action for runtime.
	void operator()(runtime& rt)
	{
		print_to_console();
	}

	// Action for zed_runtime.
	void operator()(zed_runtime& rt)
	{
		print_to_console();
	}

	base_action* clone() const
	{
		return new invalid_request(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<response>(*this);
		ar & m_request_sender_addr;
		ar & m_request_sender_port;
		ar & m_message;
	}

private:
	std::string m_request_sender_addr;
	unsigned short m_request_sender_port;
	std::string m_request_type;
	std::string m_message;
};

}
};

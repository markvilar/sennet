#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/responses/response.hpp>

namespace am {
namespace action {

class invalid_request : public response
{
public:
	// Default constructor.
	invalid_request() 
		: response(),
		m_request(0)
	{}

	// Copy constructor.
	invalid_request(const invalid_request& other)
		: response(other)
	{
		m_request = other.get_request();
	}

	// Constructor.
	invalid_request(
		const std::string sender_addr,
		const unsigned short sender_port,
		const base_action& request
		)
		: response(sender_addr, sender_port)
	{
		m_request = request.clone();
	}

	// Destructor.
	~invalid_request()
	{}

	// Prints the information of the invalid request.
	void print_to_console()
	{
		auto [addr, port] = get_sender();
		std::cout << "[AM] Invalid request. Receiver: " 
			<< addr << ":" << port << "\n";
	}

	// Gets the invalid request.
	base_action* get_request() const
	{
		if (m_request)
			return m_request->clone();
		else
			return nullptr;
	}

	// Sets the invalid request.
	inline void set_request(const base_action& r)
	{
		m_request = r.clone();
	}

	// Action for runtime.
	void operator()(runtime& rt)
	{
		// TODO: Add logging.
		print_to_console();
	}

	// Action for zed_runtime.
	void operator()(zed_runtime& rt)
	{
		// TODO: Add logging.
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
		ar & m_request;
	}

private:
	// TODO: Possibly add error message.
	base_action* m_request;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::invalid_request,
	"am::action::invalid_request");

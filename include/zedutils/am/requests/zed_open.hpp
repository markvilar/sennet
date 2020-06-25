#pragma once

#include <string>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/am/requests/request.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_open : public request
{
	typedef boost::asio::ip::tcp asio_tcp;

public:
	// Default constructor.
	zed_open()
		: request(),
		m_init_params()
	{}

	// Copy constructor.
	zed_open(const zed_open& other)
		: request(other)
	{
		m_init_params = other.m_init_params;
	}

	// Constructor.
	zed_open(
		const std::string sender_addr,
		const unsigned short sender_port,
		const sl::InitParameters& params
		)
		: request(sender_addr, sender_port),
		m_init_params(params)
	{}

	// Constructor.
	zed_open(
		const asio_tcp::endpoint& sender_ep,
		const sl::InitParameters& params
		)
		: request(sender_ep),
		m_init_params(params)
	{}

	// Destructor.
	~zed_open()
	{
	}

	// Gets the initialization parameters.
	sl::InitParameters get_params() const
	{
		return m_init_params;
	}

	// Sets the initialization parameters.
	void set_params(sl::InitParameters& params)
	{
		m_init_params = params;
	}

	// Action for runtime instances.
	void operator()(runtime& rt)
	{
		std::cout << "[AM] Cannot open zed...\n";
	}

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt)
	{
		std::cout << "[AM] Opening zed...\n";
		sl::ERROR_CODE error = rt.open_zed(m_init_params);
	}

	// Clone function.
	base_action* clone() const
	{
		return new zed_open(*this);
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<request>(*this);
		ar & m_init_params;
	}
private:
	sl::InitParameters m_init_params;
};

}
};

BOOST_CLASS_EXPORT_GUID(am::action::zed_open, 
	"am::action::zed_open");

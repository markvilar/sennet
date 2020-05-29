#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/serialization.hpp>

namespace am { namespace action {

class request_zed_open : public base_action
{
private:
	// TODO: Possibly add more members.
	sl::InitParameters m_init_params;

public:
	// Basic constructor.
	request_zed_open()
		: m_init_params()
	{
	}

	// Overloaded constructor.
	request_zed_open(sl::InitParameters ip)
		: m_init_params(ip)
	{
	}

	// Destructor.
	~request_zed_open()
	{
	}

	// Action for base runtime instances.
	void operator()(runtime& rt)
	{
		std::cout << "This is a regular runtime. Cannot open zed...\n";
		// TODO: Implement sending of invalid request.
	}

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt)
	{
		std::cout << "This is a zed_runtime. Opening zed...\n";
		sl::ERROR_CODE error = rt.open_zed(m_init_params);
	}

	// Clone function.
	base_action* clone() const
	{
		return new request_zed_open(m_init_params);
	}

	// Gets the initialization parameters.
	sl::InitParameters get_params() const
	{
		return m_init_params;
	}
	// Sets the initialization parameters.
	void set_params(sl::InitParameters params)
	{
		m_init_params = params;
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<base_action>(*this);
		ar & m_init_params;
	}
};

} // namespace action
}; // namespace am

BOOST_CLASS_EXPORT_GUID(am::action::request_zed_open, 
	"am::action::request_zed_open");

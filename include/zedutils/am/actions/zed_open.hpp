#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sl/Camera.hpp>

#include <zedutils/am/core.hpp>
#include <zedutils/serialization.hpp>

namespace am { 
namespace action {

class zed_open : public request
{

public:
	// Basic constructor.
	zed_open()
		: request(),
		m_init_params()
	{
	}

	// Overloaded constructor.
	zed_open(sl::InitParameters ip)
		: request(),
		m_init_params(ip)
	{
	}

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
	void set_params(sl::InitParameters params)
	{
		m_init_params = params;
	}

	// Action for runtime instances.
	void operator()(runtime& rt)
	{
		std::cout << "This is a regular runtime. Cannot open zed...\n";
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
		return new zed_open(m_init_params);
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

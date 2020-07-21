#pragma once

#include <iostream>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include <sennet/am/core.hpp>
#include <sennet/core/log.hpp>

namespace am { namespace action {

class hello_world : public base_action
{
public:
	hello_world()
	{
	}

	~hello_world()
	{
	}

	void operator()(runtime& rt)
	{
		std::cout << "hello world\n";
	}

	void operator()(zed_runtime& rt)
	{
		std::cout << "hello world\n";
	}

	base_action* clone() const
	{
		return new hello_world;
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<base_action>(*this);
	}
};

} // namespace action
}; // namespace am

BOOST_CLASS_EXPORT_GUID(am::action::hello_world, 
	"am::action::hello_world");

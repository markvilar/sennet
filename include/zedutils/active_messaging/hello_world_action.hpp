#include <boost/serialization/export.hpp>

#include <zedutils/active_messaging/action.hpp>
#include <zedutils/active_messaging/runtime.hpp>

namespace zed { namespace am {

class hello_world_action : public action
{
public:
	void operator()(runtime& rt)
	{
		std::cout << "hello world\n";
		rt.stop();
	}

	action* clone() const
	{
		return new hello_world_action;
	}

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<action>(*this);
	}
}; // class hello_world_action

}
};

BOOST_CLASS_EXPORT_GUID(zed::am::hello_world_action, "hello_world_action");

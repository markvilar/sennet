#include <zedutils/active_messaging/action.hpp>

namespace zed { namespace am {

// ----------------------------- hello_world_action ----------------------------

hello_world_action::hello_world_action()
{
}

hello_world_action::~hello_world_action()
{
}

void hello_world_action::operator()(runtime& rt)
{
}

void hello_world_action::operator()(zed_runtime& rt)
{
}

action* hello_world_action::clone() const
{
	return new hello_world_action;
}

template <typename Archive>
void hello_world_action::serialize(Archive& ar, const unsigned int version)
{
	ar & boost::serialization::base_object<action>(*this);
}

// ----------------------------- open_camera_request ---------------------------

open_camera_request::open_camera_request()
	: m_init_params()
{
}

open_camera_request::open_camera_request(sl::InitParameters ip)
	: m_init_params(ip)
{
}

open_camera_request::~open_camera_request()
{
}

void open_camera_request::operator()(runtime& rt)
{
	std::cout << "This is not a zed_runtime. Cannot open camera...\n";
}

void open_camera_request::operator()(zed_runtime& rt)
{
	std::cout << "This is a zed_runtime. Opening camera...\n";
	sl::ERROR_CODE error = rt.open_camera(m_init_params);
}

action* open_camera_request::clone() const
{
	return new open_camera_request(m_init_params);
}

sl::InitParameters open_camera_request::get_params() const
{
	return m_init_params;
}

void open_camera_request::set_params(sl::InitParameters params)
{
	m_init_params = params;
}

template <typename Archive>
void open_camera_request::serialize(Archive& ar, const unsigned int version)
{
	ar & boost::serialization::base_object<action>(*this);
	ar & m_init_params;
};


// ---------------------------- close_camera_action ----------------------------

close_camera_request::close_camera_request()
{
}

close_camera_request::~close_camera_request()
{
};

void close_camera_request::operator()(runtime& rt)
{
	std::cout << "This is not a zed_runtime. Cannot close camera...\n";
}

void close_camera_request::operator()(zed_runtime& rt)
{
	std::cout << "This is a zed_runtime. Closing camera...\n";
	rt.close_camera();
}

action* close_camera_request::clone() const
{
	return new close_camera_request();
}

template <typename Archive>
void close_camera_request::serialize(Archive& ar, const unsigned int version)
{
	ar & boost::serialization::base_object<action>(*this);
}

} // namespace am
}; // namespace zed


// ------------------------------ Export actions -------------------------------

BOOST_CLASS_EXPORT_GUID(zed::am::hello_world_action, 
	"zed::am::hello_world_action");
BOOST_CLASS_EXPORT_GUID(zed::am::open_camera_request, 
	"zed::am::open_camera_request");
BOOST_CLASS_EXPORT_GUID(zed::am::close_camera_request,
	"zed::am::close_camera_request");

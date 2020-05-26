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
	std::cout << "hello world\n";
}

void hello_world_action::operator()(zed_runtime& rt)
{
	std::cout << "hello world\n";
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

// ----------------------------- zed_open_request ---------------------------

zed_open_request::zed_open_request()
	: m_init_params()
{
}

zed_open_request::zed_open_request(sl::InitParameters ip)
	: m_init_params(ip)
{
}

zed_open_request::~zed_open_request()
{
}

void zed_open_request::operator()(runtime& rt)
{
	std::cout << "This is a regular runtime. Cannot open zed...\n";
	// TODO: Implement sending of invalid request.
}

void zed_open_request::operator()(zed_runtime& rt)
{
	std::cout << "This is a zed_runtime. Opening zed...\n";
	sl::ERROR_CODE error = rt.open_zed(m_init_params);
}

action* zed_open_request::clone() const
{
	return new zed_open_request(m_init_params);
}

sl::InitParameters zed_open_request::get_params() const
{
	return m_init_params;
}

void zed_open_request::set_params(sl::InitParameters params)
{
	m_init_params = params;
}

template <typename Archive>
void zed_open_request::serialize(Archive& ar, const unsigned int version)
{
	ar & boost::serialization::base_object<action>(*this);
	ar & m_init_params;
};


// ---------------------------- zed_close_request ----------------------------

zed_close_request::zed_close_request()
{
}

zed_close_request::~zed_close_request()
{
};

void zed_close_request::operator()(runtime& rt)
{
	std::cout << "This is a regular runtime. Cannot close zed...\n";
	// TODO: Implement sending of invalid request.
}

void zed_close_request::operator()(zed_runtime& rt)
{
	std::cout << "This is a zed_runtime. Closing zed...\n";
	rt.close_zed();
}

action* zed_close_request::clone() const
{
	return new zed_close_request();
}

template <typename Archive>
void zed_close_request::serialize(Archive& ar, const unsigned int version)
{
	ar & boost::serialization::base_object<action>(*this);
}

} // namespace am
}; // namespace zed


// ------------------------------ Export actions -------------------------------

BOOST_CLASS_EXPORT_GUID(zed::am::hello_world_action, 
	"zed::am::hello_world_action");
BOOST_CLASS_EXPORT_GUID(zed::am::zed_open_request, 
	"zed::am::zed_open_request");
BOOST_CLASS_EXPORT_GUID(zed::am::zed_close_request,
	"zed::am::zed_close_request");

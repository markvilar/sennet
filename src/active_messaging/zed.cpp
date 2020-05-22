#include <zedutils/active_messaging/zed.hpp>

namespace zed { namespace am {

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

// -------------------------------- zed_runtime --------------------------------

zed_runtime::zed_runtime(
	std::string port,
	std::string root,
	std::function<void(runtime&)> f,
	boost::uint64_t wait_for
	)
	: runtime(port, f, wait_for),
	m_camera(),
	m_root(root)
{
}

zed_runtime::~zed_runtime()
{
	// Stop I/O service and execution thread.
	stop();

	// Close camera.
	close_camera();
}

sl::ERROR_CODE zed_runtime::open_camera(sl::InitParameters& init_params)
{
	// TODO: Possibly add some assertions?
	return m_camera.open(init_params);
}

void zed_runtime::close_camera()
{
	// TODO: Possibly add some assertions?
	m_camera.close();
}

} // namespace am
}; // namespace zed

// ------------------------------ Export actions -------------------------------

BOOST_CLASS_EXPORT_GUID(zed::am::open_camera_request, 
	"zed::am::open_camera_request");
BOOST_CLASS_EXPORT_GUID(zed::am::close_camera_request,
	"zed::am::close_camera_request");

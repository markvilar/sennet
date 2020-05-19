#include <zedutils/active_messaging/zed.hpp>

namespace zed { namespace am {

// ----------------------------- open_camera_action ----------------------------

open_camera_action::open_camera_action()
	: m_init_params()
{
}

open_camera_action::~open_camera_action()
{
}

void open_camera_action::operator()(runtime& rt)
{
	std::cout << "This is not a zed_runtime. Cannot open camera...\n";
}

void open_camera_action::operator()(zed_runtime& rt)
{
	std::cout << "This is a zed_runtime. Opening camera...\n";
	sl::ERROR_CODE error = rt.open_camera(m_init_params);
}

action* open_camera_action::clone() const
{
	// TODO: Implement copying of m_init_params!
	return new open_camera_action;
}

template <typename Archive>
void open_camera_action::serialize(Archive& ar, const unsigned int version)
{
	// TODO: Implement serialization function for sl::InitParameters.
	ar & boost::serialization::base_object<action>(*this);
	ar & m_init_params;
};

// ---------------------------- close_camera_action ----------------------------

close_camera_action::close_camera_action()
{
}

close_camera_action::~close_camera_action()
{
};

void close_camera_action::operator()(runtime& rt)
{
	std::cout << "This is not a zed_runtime. Cannot close camera...\n";
}

void close_camera_action::operator()(zed_runtime& rt)
{
	std::cout << "This is a zed_runtime. Closing camera...\n";
	rt.close_camera();
}

action* close_camera_action::clone() const
{
	return new close_camera_action;
}

template <typename Archive>
void close_camera_action::serialize(Archive& ar, const unsigned int version)
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

sl::ERROR_CODE zed_runtime::open_camera(sl::InitParameters init_params)
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

BOOST_CLASS_EXPORT_GUID(zed::am::open_camera_action, 
	"zed::am::open_camera_action");
BOOST_CLASS_EXPORT_GUID(zed::am::close_camera_action,
	"zed::am::close_camera_action");


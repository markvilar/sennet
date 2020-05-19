#ifndef AM_ZED_HPP
#define AM_ZED_HPP

#include <iostream>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/tracking.hpp>

#include <sl/Camera.hpp>

#include <zedutils/active_messaging/core.hpp>
#include <zedutils/serialization.hpp>

namespace zed { namespace am {

// Forward declaration.
class zed_runtime;

// ----------------------------- open_camera_action ----------------------------

class open_camera_action : public action
{
private:
	// TODO: Possibly add more members.
	sl::InitParameters m_init_params;

public:
	// TODO: Possibly add overloaded constructor.
	open_camera_action();

	~open_camera_action();

	// Action for base runtime instances.
	void operator()(runtime& rt);

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt);

	// Clone function.
	action* clone() const;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version);
}; // class open_camera_action


// ---------------------------- close_camera_action ----------------------------

class close_camera_action : public action
{
private:
	
public:
	close_camera_action();

	~close_camera_action();
	
	// Action for base runtime instances.
	void operator()(runtime& rt);

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt);

	// Clone function.
	action* clone() const;

	// Function for serializing with Boost.Serialization.
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version);
}; // class close_camera_action


// -------------------------------- zed_runtime --------------------------------

class zed_runtime : private runtime
{
private:
	// ZED camera.
	sl::Camera m_camera;

	// Path to root directory for data storage.
	std::string m_root;

public:
	zed_runtime(
		std::string port, 
		std::string root,
		std::function<void(runtime&)> f 
			= std::function<void(runtime&)>(),
		boost::uint64_t wait_for = 1
		);

	~zed_runtime();

	// Opens the ZED camera.
	sl::ERROR_CODE open_camera(sl::InitParameters init_params);

	// Closes the ZED camera.
	void close_camera();

}; // class zed_runtime

} // namespace am
}; // namespace zed

#endif // AM_ZED_HPP

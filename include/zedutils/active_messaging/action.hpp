#ifndef ACTION_HPP
#define ACTION_HPP

#include <iostream>

#include <sl/Camera.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/tracking.hpp>

#include <zedutils/active_messaging/runtime.hpp>
#include <zedutils/serialization.hpp>

namespace zed { namespace am {

// Forward declaration
class runtime;
class zed_runtime;


// ---------------------------------- action -----------------------------------

class action 
{
private:

public:
	virtual ~action() {}
	
	virtual void operator()(runtime& rt) = 0;
	virtual void operator()(zed_runtime& rt) = 0;

	virtual action* clone() const = 0;

	// Member function needed in order to use Boost.Serialization.
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {};
}; // class action


// ----------------------------- hello_world_action ----------------------------

class hello_world_action : public action
{
public:
	hello_world_action();

	~hello_world_action();

	void operator()(runtime& rt);

	void operator()(zed_runtime& rt);

	action* clone() const;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version);
}; // class hello_world_action


// ----------------------------- zed_open_request ---------------------------

class zed_open_request : public action
{
private:
	// TODO: Possibly add more members.
	sl::InitParameters m_init_params;

public:
	// Basic constructor.
	zed_open_request();

	// Overloaded constructor.
	zed_open_request(sl::InitParameters ip);

	// Destructor.
	~zed_open_request();

	// Action for base runtime instances.
	void operator()(runtime& rt);

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt);

	// Clone function.
	action* clone() const;

	// Gets the initialization parameters.
	sl::InitParameters get_params() const;

	// Sets the initialization parameters.
	void set_params(sl::InitParameters params);

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version);
}; // class zed_open_request


// ---------------------------- zed_close_request ---------------------------

class zed_close_request : public action
{
private:
	
public:
	zed_close_request();

	~zed_close_request();
	
	// Action for base runtime instances.
	void operator()(runtime& rt);

	// Action for zed_runtime instances.
	void operator()(zed_runtime& rt);

	// Clone function.
	action* clone() const;

	// Function for serializing with Boost.Serialization.
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version);
}; // class zed_close_request

} // namespace am
}; // namespace zed

#endif // ACTION_HPP

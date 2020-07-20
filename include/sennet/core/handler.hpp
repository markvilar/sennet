#pragma once

#include <sennet/snpch.hpp>

namespace sennet
{

enum class handler_type
{
	none = 0,
	zed_recorder
};

// Macro to implement handler type functions.
#define HANDLER_CLASS_TYPE(type) \
	static handler_type get_static_type() \
		{ return handler_type::type; } \
	virtual handler_type get_handler_type() const override \
		{ return get_static_type(); } \
	virtual const char* get_name() const override \
		{ return #type; }
	

class handler
{
	// Basic handler interface class.

public:
	// Deconstructor.
	virtual ~handler() = default;

	// Opens the handle.
	virtual void open() = 0;

	// Closes the handle.
	virtual void close() = 0;

	// Checks if the handle is open.
	virtual bool is_opened() const = 0;
	
	// Returns the name of the handler.
	virtual const char* get_name() const = 0;

	// Returns the static handler type.
	virtual handler_type get_handler_type() const = 0;

	// Returns a string representation of the handler.
	virtual std::string to_string() const { return get_name(); }
};

};

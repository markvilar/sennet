#pragma once

#include <sennet/pch.hpp>

#include <sennet/core/base.hpp>

namespace sennet
{

enum class source_handle_type
{
	none = 0,
	zed_recorder
};

#define SOURCE_HANDLE_CLASS_TYPE(type) \
	static source_handle_type get_static_type() \
		{ return source_handle_type::type; } \
	virtual source_handle_type get_source_handle_type() const override \
		{ return get_static_type(); } \
	virtual const char* get_name() const override \
		{ return #type; }

class source_handle
{
	// Basic source handle interface class.

public:
	virtual ~source_handle() = default;

	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual source_handle_type get_source_handle_type() const = 0;
	virtual const char* get_name() const = 0;
	virtual std::string to_string() const { return get_name(); }
};

};

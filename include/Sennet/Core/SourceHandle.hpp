#pragma once

#include <Sennet/pch.hpp>

#include <Sennet/Core/Base.hpp>

namespace Sennet
{

enum class SourceHandleType
{
	None = 0,
	ZEDRecorder
};

#define SOURCE_HANDLE_CLASS_TYPE(type) \
	static SourceHandleType GetStaticType() \
		{ return SourceHandleType::type; } \
	virtual SourceHandleType GetSourceHandleType() const override \
		{ return GetStaticType(); } \
	virtual const char* GetName() const override \
		{ return #type; }

class SourceHandle
{
	// Basic source handle interface class.

public:
	virtual ~SourceHandle() = default;

	virtual void Init() = 0;
	virtual void Shutdown() = 0;

	virtual SourceHandleType GetSourceHandleType() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const { return GetName(); }
};

};

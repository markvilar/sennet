#pragma once

#include <sennet/pch.hpp>

#include <sennet/core/base.hpp>
#include <sennet/events/event.hpp>

namespace sennet
{

class layer
{
public:
	layer(const std::string& name = "layer");
	virtual ~layer() = default;

	virtual void on_attach() {}
	virtual void on_detach() {}
	virtual void on_update() {}
	virtual void on_event(event& e) {}

	inline const std::string& get_name() const { return m_name; }

protected:
	std::string m_name;
};

}

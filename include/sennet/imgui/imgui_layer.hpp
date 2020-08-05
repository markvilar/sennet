#pragma once

#include <sennet/core/layer.hpp>

#include <sennet/events/application_event.hpp>
#include <sennet/events/key_event.hpp>
#include <sennet/events/mouse_event.hpp>

namespace sennet
{

class imgui_layer : public layer
{
public:
	imgui_layer();
	~imgui_layer() = default;

	virtual void on_attach() override;
	virtual void on_detach() override;
	virtual void on_imgui_render() override;

	void begin();
	void end();

private:

private:
	float m_time;

};

}

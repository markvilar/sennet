#include <sennet/pch.hpp>
#include <sennet/core/application.hpp>

#include <glad/glad.h>

#include <sennet/core/log.hpp>
#include <sennet/core/input.hpp>

namespace sennet
{

application* application::s_instance = nullptr;

application::application()
{
	SN_CORE_ASSERT(!s_instance, "Application already exists!");
	s_instance = this;

	m_window = window::create();
	m_window->set_event_callback(SN_BIND_EVENT_FN(application::on_event));

	m_imgui_layer = new imgui_layer();
	push_overlay(m_imgui_layer);
}

application::~application()
{
}

void application::on_event(event& e)
{
	// Dispatch event.
	event_dispatcher dispatcher(e);
	dispatcher.dispatch<window_close_event>(
		SN_BIND_EVENT_FN(application::on_window_close));

	// Propagate event through layers.
	for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); )
	{
		(*--it)->on_event(e);
		if (e.handled)
		{
			break;
		}
	}
}

void application::push_layer(layer* lay)
{
	m_layer_stack.push_layer(lay);
	lay->on_attach();
}

void application::push_overlay(layer* lay)
{
	m_layer_stack.push_overlay(lay);
	lay->on_attach();
}

void application::close()
{
}

void application::run()
{
	while (m_running)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (layer* lay : m_layer_stack)
		{
			lay->on_update();
		}
		
		// Imgui rendering.
		m_imgui_layer->begin();
		for (layer* lay : m_layer_stack)
		{
			lay->on_imgui_render();
		}
		m_imgui_layer->end();

		m_window->on_update();
	}
}

bool application::on_window_close(window_close_event& e)
{
	m_running = false;
	return true;
}

bool application::on_window_resize(window_resize_event& e)
{
	return true;
}

};

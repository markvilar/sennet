#pragma once

#include <sennet/core/base.hpp>

#include <sennet/core/window.hpp>
#include <sennet/core/layer_stack.hpp>

#include <sennet/events/event.hpp>
#include <sennet/events/application_event.hpp>

#include <sennet/imgui/imgui_layer.hpp>

namespace sennet
{

// TODO: Look into an alternative to sennet::main function!
int main(int argc, char** argv);

class application
{
public:
	application();
	virtual ~application();

	void on_event(event& e);

	void push_layer(layer* lay);
	void push_overlay(layer* lay);

	window& get_window() { return *m_window; }

	void close();

	static application& get() { return *s_instance; }

private:
	void run();
	bool on_window_close(window_close_event& e);
	bool on_window_resize(window_resize_event& e);

private:
	scope<window> m_window;
	imgui_layer* m_imgui_layer;
	bool m_running = true;
	layer_stack m_layer_stack;

private:
	static application* s_instance;
	friend int main(int argc, char** argv);
};

// To be defined in client.
application* create_application();

}

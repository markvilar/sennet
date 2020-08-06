#pragma once

#include <sennet/core/base.hpp>

#include <sennet/core/window.hpp>
#include <sennet/core/layer_stack.hpp>

#include <sennet/events/event.hpp>
#include <sennet/events/application_event.hpp>

#include <sennet/imgui/imgui_layer.hpp>

// Temporary.
#include <sennet/renderer/buffer.hpp>
#include <sennet/renderer/shader.hpp>
#include <sennet/renderer/vertex_array.hpp>

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

	// Temporary.
	ref<shader> m_shader;
	ref<vertex_array> m_vertex_array;
	ref<vertex_buffer> m_vertex_buffer;
	ref<index_buffer> m_index_buffer;

	ref<shader> m_blue_shader;
	ref<vertex_array> m_square_va;
private:
	static application* s_instance;
	friend int main(int argc, char** argv);
};

// To be defined in client.
application* create_application();

}

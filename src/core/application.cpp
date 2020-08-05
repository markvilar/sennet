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

	// Vertex array
	// Vertex buffer
	// Index buffer

	// Temporary
	glGenVertexArrays(1, &m_vertex_array);
	glBindVertexArray(m_vertex_array);

	glGenBuffers(1, &m_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);

	float vertices[3*3] = 
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);

	glGenBuffers(1, &m_index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);

	unsigned int indices[3] = { 0, 1, 2 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);
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
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(m_vertex_array);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

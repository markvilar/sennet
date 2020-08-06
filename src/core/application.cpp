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

	float vertices[3 * 3] = 
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	m_vertex_buffer.reset(vertex_buffer::create(vertices, sizeof(vertices)));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);

	uint32_t indices[3] = { 0, 1, 2 };

	m_index_buffer.reset(index_buffer::create(indices, 
		sizeof(indices) / sizeof(uint32_t)));

	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec3 a_position;

		out vec3 v_position;

		void main()
		{
			v_position = a_position;
			gl_Position = vec4(a_position, 1.0);
		}
	)";

	std::string fragment_src = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_position;

		void main()
		{
			color = vec4(v_position * 0.5 + 0.5, 1.0);
		}
	)";

	m_shader.reset(new shader(vertex_src, fragment_src));
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

		m_shader->bind();
		glBindVertexArray(m_vertex_array);
		glDrawElements(GL_TRIANGLES, m_index_buffer->get_count(), 
			GL_UNSIGNED_INT, nullptr);

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

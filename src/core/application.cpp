#include <sennet/snpch.hpp>
#include <sennet/core/application.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sennet
{

application::application()
{
	m_window = window::create();
}

application::~application()
{
}

void application::on_event()
{
}

void application::get_window()
{
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
		m_window->on_update();
	}
}

bool application::on_window_close()
{
}

bool application::on_window_resize()
{
}

};

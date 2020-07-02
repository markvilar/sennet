#include <sennet/application.hpp>

namespace sennet
{

application::application(am::runtime& rt, const std::string& name)
	: m_name(name),
	m_runtime(rt)
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
}

bool application::on_window_close()
{
}

bool application::on_window_resize()
{
}

};

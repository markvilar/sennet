#pragma once

#include <sennet/core/base.hpp>
#include <sennet/events/event.hpp>
#include <sennet/core/window.hpp>

namespace sennet
{

class application
{
public:
	application();
	
	virtual ~application();
	void on_event();
	void get_window();
	void close();

	void run();

	static application& get() { return *s_instance; }

private:
	bool on_window_close();
	bool on_window_resize();

private:
	scope<window> m_window;
	bool m_running = true;

private:
	static application* s_instance;

	friend int main(int argc, char** argv);
};

// To be defined in client.
application* create_application();

};

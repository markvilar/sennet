#pragma once

#include <sennet/snpch.hpp>

#include <sennet/am/core.hpp>

namespace sennet
{

class application
{
public:
	application(am::runtime& rt, const std::string& name = "Sennet App");
	
	virtual ~application();

	void on_event();

	void get_window();

	void close();

	static application& get() { return *s_instance; }

private:
	void run();

	bool on_window_close();

	bool on_window_resize();

private:
	const std::string m_name;

	am::runtime& m_runtime;

	// std::unique_ptr<window> m_window;

private:
	static application* s_instance;

	friend int main(int argc, char** argv);
};

// To be defined in client.
application* create_application();

};

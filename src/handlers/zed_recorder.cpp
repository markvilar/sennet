#include <sennet/handlers/zed_recorder.hpp>

namespace sennet
{

zed_recorder::zed_recorder()
	: m_init_params(),
	m_rec_params(),
	m_run_params(),
	m_zed(),
	m_close_flag(true),
	m_stop_flag(true),
	m_mutex(),
	m_exec_thread()
{
	SN_INFO("[{}] Initialized.", get_name());
}

zed_recorder::~zed_recorder()
{
	if (not m_close_flag)
	{
		close();
	}
}

void zed_recorder::open()
{
	SN_INFO("[{}] Opening.", get_name());
	if (m_close_flag)
	{
		m_close_flag = false;
		// TODO: Problem here! Look into starting the thread properly.
		m_exec_thread = std::thread(&zed_recorder::exec_worker, this);
	}
}

void zed_recorder::close() 
{
	if (not m_stop_flag)
	{
		stop();
	}
	m_close_flag = true;
	SN_INFO("[{}] Joining threads.", get_name());
	m_exec_thread.join();
	SN_INFO("[{}] Closing.", get_name());
}

bool zed_recorder::is_opened() const
{
	return (not m_close_flag);
}

std::string zed_recorder::to_string() const
{
	// TODO: Implement.
}

void zed_recorder::run()
{
	// TODO: Add checking of execution thread.
	if (m_stop_flag)
	{
		m_stop_flag = false;
	}
}

void zed_recorder::stop()
{
	if (not m_stop_flag)
	{
		m_stop_flag = true;
		SN_INFO("[{}] Stopping.", get_name());
	}
}

bool zed_recorder::is_zed_opened()
{
	return m_zed.isOpened();
}

zed::image zed_recorder::get_image() const
{
	// TODO: Implement.
}

zed::state zed_recorder::get_state() const
{
	// TODO: Implement.
}

zed::init_params zed_recorder::get_init_params() const
{
	// TODO: Implement.
}

zed::recording_params zed_recorder::get_rec_params() const
{
	// TODO: Implement.
}

zed::runtime_params zed_recorder::get_run_params() const
{
	// TODO: Implement.
}

void zed_recorder::set_init_params(const zed::init_params& init_params)
{
	// TODO: Implement.
}

void zed_recorder::set_rec_params(const zed::recording_params& rec_params)
{
	// TODO: Implement.
}

void zed_recorder::set_run_params(const zed::runtime_params& run_params)
{
	// TODO: Implement.
}

void zed_recorder::exec_worker()
{
	// TODO: Open ZED.
	while (not m_close_flag)
	{
		run_loop();
	}
	// TODO: Close ZED.
}

void zed_recorder::run_loop()
{
	while (not m_stop_flag)
	{
		SN_INFO("[{}] Running.", get_name());
	}
}

};

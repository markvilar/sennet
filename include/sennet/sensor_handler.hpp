#pragma once

#include <atomic>
#include <mutex>
#include <thread>

namespace sennet 
{

class sensor_handler
{
public:
	sensor_handler();

	~sensor_handler();

	virtual bool open();

	virtual bool close();

	virtual void run();

	virtual void shutdown();

private:
	std::atomic<bool> m_open_flag;
	std::atomic<bool> m_run_flag;

	std::thread m_exec_thread;

	// The handler exec loop.
	virtual void run_worker() = 0;
};

};

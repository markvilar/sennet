#include <sennet/zed/recorder.hpp>

#include <sennet/zed/conversion.hpp>

namespace sennet
{

namespace zed
{

recorder::recorder()
	: m_init_params(::sennet::create_ref<sl::InitParameters>()),
	m_rec_params(::sennet::create_ref<sl::RecordingParameters>()),
	m_run_params(::sennet::create_ref<sl::RuntimeParameters>()),
	m_zed(::sennet::create_scope<sl::Camera>()),
	m_running(false),
	m_recording(false),
	m_mutex(::sennet::create_scope<std::mutex>()),
	m_exec_thread(),
	m_worker_timeout(100),
	m_record_timeout(10)
{
	init();
}

recorder::~recorder()
{
	shutdown();
}

void recorder::init()
{
	if (m_running)
	{
		SN_CORE_WARN("[{0}] Already initialized.", get_name());
		return;
	}
	else if (not m_running and m_recording)
	{
		SN_CORE_ERROR("[{0}] Critical situation! Forcing \
			shutdown and re-initialization.", get_name());
	}
	else if (not m_running and not m_recording)
	{
		SN_CORE_INFO("[{0}] Starting initialization.", get_name());
	}

	stop_exec_thread();
	join_exec_thread();
	start_exec_thread();
}

void recorder::shutdown()
{
	if (not m_running and not m_recording)
	{
		SN_CORE_WARN("[{0}] Already shut down.", get_name());
	}
	else if (not m_running and m_recording)
	{
		SN_CORE_ERROR("[{0}] Critical situation! Forcing shutdown.",
			get_name());
	}
	else if (m_running and not m_recording)
	{
		SN_CORE_INFO("[{0}] Starting shutdown.", get_name());
	}

	stop_exec_thread();
	join_exec_thread();
}

std::string recorder::to_string() const
{
	// TODO: Implement.
	return std::string("");
}

void recorder::start_record()
{
	if (not m_running)
	{
		SN_CORE_INFO("[{0}] Not initialized, cannot record.",
			get_name());
	}
	else if (m_running and m_recording)
	{
		SN_CORE_INFO("[{0}] Already recording.", get_name());
		m_should_record = true;
	}
	else if (m_running and not m_recording)
	{
		SN_CORE_INFO("[{0}] Starting record.", get_name());
		m_should_record = true;
	}
}

void recorder::stop_record()
{
	if (m_running and not m_recording)
	{
		SN_CORE_INFO("[{0}] Not recording.", get_name());
	}
	else if (m_running and m_recording)
	{
		SN_CORE_INFO("[{0}] Stopping record.", get_name());
	}
	m_should_record = false;
}

bool recorder::is_zed_opened() const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	return m_zed->isOpened();
}

::sennet::ref<image> recorder::get_image(const zed::view& view) const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	if (m_zed->isOpened())
	{
		auto m = create_ref<sl::Mat>();
		m_zed->retrieveImage(*m, ::to_stereolabs(view));
		return ::to_sennet(m);
	}
	else
	{
		return nullptr;
	}
}

::sennet::ref<init_params> recorder::get_init_params() const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	return ::to_sennet(m_init_params);
}

::sennet::ref<recording_params> recorder::get_rec_params() const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	return ::to_sennet(m_rec_params);
}

::sennet::ref<runtime_params> recorder::get_run_params() const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	return ::to_sennet(m_run_params);
}

::sennet::ref<init_params> recorder::get_zed_init_params() const
{
	if (not is_zed_opened())
	{
		SN_CORE_WARN("[{0}] ZED is closed.", get_name());
		return nullptr;
	}
	else
	{
		m_mutex->lock();
		auto params = create_ref<sl::InitParameters>(
			m_zed->getInitParameters());
		m_mutex->unlock();
		return ::to_sennet(params);
	}
}

ref<zed::recording_params> recorder::get_zed_rec_params() const
{
	if (not is_zed_opened())
	{
		SN_CORE_WARN("[{0}] ZED is closed.", get_name());
		return nullptr;
	}
	else
	{
		m_mutex->lock();
		auto params = create_ref<sl::RecordingParameters>(
			m_zed->getRecordingParameters());
		m_mutex->unlock();
		return ::to_sennet(params);
	}
}

ref<zed::runtime_params> recorder::get_zed_run_params() const
{
	if (not is_zed_opened())
	{
		SN_CORE_WARN("[{0}] ZED is closed.", get_name());
		return nullptr;
	}
	else
	{
		m_mutex->lock();
		auto params = create_ref<sl::RuntimeParameters>(
			m_zed->getRuntimeParameters());
		m_mutex->unlock();
		return ::to_sennet(params);
	}
}

void recorder::set_init_params(const ref<zed::init_params> init_params)
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	m_init_params = ::to_stereolabs(init_params);
}

void recorder::set_rec_params(const ref<zed::recording_params> rec_params)
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	m_rec_params = ::to_stereolabs(rec_params);
}

void recorder::set_run_params(const ref<zed::runtime_params> run_params)
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	m_run_params = ::to_stereolabs(run_params);
}

void recorder::exec_worker()
{
	m_running = true;
	SN_CORE_INFO("[{0}] Execution worker started.", get_name());
	while (m_should_run)
	{
		if (m_should_record)
		{
			record_loop();
		}
		std::this_thread::sleep_for(m_worker_timeout);
	}
	SN_CORE_INFO("[{0}] Execution worker finished.", get_name());
	m_running = false;
}

void recorder::record_loop()
{
	m_recording = true;
	SN_CORE_INFO("[{0}] Record loop started.", get_name());

	m_mutex->lock();
	auto open_error = m_zed->open(*m_init_params);
	m_mutex->unlock();
	if (open_error != sl::ERROR_CODE::SUCCESS)
	{
		SN_CORE_WARN("[{0}] Could not open ZED!", get_name());
	}
	else
	{
		SN_CORE_INFO("[{0}] ZED opened.", get_name());
	}

	m_mutex->lock();
	auto record_error = m_zed->enableRecording(*m_rec_params);
	m_mutex->unlock();
	if (record_error != sl::ERROR_CODE::SUCCESS)
	{
		SN_CORE_WARN("[{0}] ZED couldn't enable recording!", get_name());
	}
	else
	{
		SN_CORE_INFO("[{0}] ZED recording enabled.", get_name());
	}

	sl::ERROR_CODE grab_error;
	SN_CORE_INFO("[{0}] ZED recording.", get_name());
	while (m_should_record)
	{
		m_mutex->lock();
		grab_error = m_zed->grab(*m_run_params);
		m_mutex->unlock();
		if (grab_error != sl::ERROR_CODE::SUCCESS)
		{
			SN_CORE_WARN("[{0}] ZED grab failed!", get_name());
		}

		std::this_thread::sleep_for(m_record_timeout);
	}

	m_mutex->lock();
	m_zed->close();
	m_mutex->unlock();

	SN_CORE_INFO("[{0}] Record loop finished.", get_name());
	m_recording = false;
}

void recorder::start_exec_thread()
{
	m_should_run = true;
	m_exec_thread = ::sennet::create_scope<std::thread>(
		&recorder::exec_worker, this);
}

void recorder::stop_exec_thread()
{
	stop_record();
	m_should_run = false;
}

void recorder::join_exec_thread()
{
	if (not m_exec_thread)
	{
		return;
	}
	else if (m_exec_thread->joinable())
	{
		m_exec_thread->join();
		SN_CORE_INFO("[{0}] Joined execution thread.", 
			get_name());
	}
}

}

}

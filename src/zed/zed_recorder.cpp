#include <sennet/zed/zed_recorder.hpp>

#include <sennet/zed/conversion.hpp>

namespace sennet
{

zed_recorder::zed_recorder()
	: m_init_params(create_ref<sl::InitParameters>()),
	m_rec_params(create_ref<sl::RecordingParameters>()),
	m_run_params(create_ref<sl::RuntimeParameters>()),
	m_zed(create_scope<sl::Camera>()),
	m_running(false),
	m_recording(false),
	m_mutex(create_scope<std::mutex>()),
	m_exec_thread(nullptr),
	m_worker_timeout(100),
	m_record_timeout(10)
{
	init();
}
zed_recorder::~zed_recorder()
{
	if (m_running and m_exec_thread->joinable())
	{
		shutdown();
	}
}

void zed_recorder::init()
{
	// TODO: Join threads properly.
	if (m_running.load())
	{
		SN_CORE_INFO("[{0}] Already initialized.", get_name());
	}
	else
	{
		SN_CORE_INFO("[{0}] Initialized.", get_name());
		m_running.store(true);
		m_exec_thread = create_scope<std::thread>(
			&zed_recorder::exec_worker, this);
	}
}

void zed_recorder::shutdown()
{
	// TODO: Join threads properly.
	if (m_running.load())
	{
		if (m_recording)
		{
			stop_record();
		}
		m_running.store(false);
		m_exec_thread->join();
	}
	else
	{
	}
	SN_CORE_INFO("[{0}] Shutdown.", get_name());
}

std::string zed_recorder::to_string() const
{
	// TODO: Implement.
	return std::string("");
}

void zed_recorder::start_record()
{
	if (!m_running.load())
	{
		SN_CORE_INFO("[{0}] Not initialized, cannot record.",
			get_name());
	}
	else if (m_running.load() and m_recording.load())
	{
		SN_CORE_INFO("[{0}] Already recording.", get_name());
	}
	else if (m_running.load() and not m_recording.load())
	{
		SN_CORE_INFO("[{0}] Start record.", get_name());
		m_recording.store(true);
	}
}

void zed_recorder::stop_record()
{
	if (!m_running.load())
	{
		SN_CORE_INFO("[{0}] Not initialized, cannot stop record.",
			get_name());
	}
	else if (m_running.load() and not m_recording.load())
	{
		SN_CORE_INFO("[{0}] Not recording.", get_name());
	}
	else if (m_running.load() and m_recording.load())
	{
		SN_CORE_INFO("[{0}] Stop record.", get_name());
		m_recording.store(false);
	}
	
}

bool zed_recorder::is_zed_opened()
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	return m_zed->isOpened();
}

ref<zed::image> zed_recorder::get_image(const zed::view& view) const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	if (m_zed->isOpened())
	{
		sl::Mat m;
		m_zed->retrieveImage(m, ::to_stereolabs(view));
		//return to_sennet(m);
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

ref<zed::init_params> zed_recorder::get_init_params() const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	//return ::to_sennet(*m_init_params);
	return nullptr;
}

ref<zed::recording_params> zed_recorder::get_rec_params() const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	//return ::to_sennet(*m_rec_params);
	return nullptr;
}

ref<zed::runtime_params> zed_recorder::get_run_params() const
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	//return ::to_sennet(*m_run_params);
	return nullptr;
}

void zed_recorder::set_init_params(const ref<zed::init_params> init_params)
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	m_init_params = ::to_stereolabs(init_params);
}

void zed_recorder::set_rec_params(const ref<zed::recording_params> rec_params)
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	m_rec_params = ::to_stereolabs(rec_params);
}

void zed_recorder::set_run_params(const ref<zed::runtime_params> run_params)
{
	std::lock_guard<std::mutex> lock(*m_mutex);
	m_run_params = ::to_stereolabs(run_params);
}

void zed_recorder::exec_worker()
{
	while (m_running.load())
	{
		record_loop();
		std::this_thread::sleep_for(m_worker_timeout);
	}
}

void zed_recorder::record_loop()
{
	// Get parameters

	// Open camera

	// Enable recording

	// Record
	while (m_recording.load())
	{
		SN_CORE_INFO("Recording...");
		std::this_thread::sleep_for(m_record_timeout);
	}

	// Close camera
}

}

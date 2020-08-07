#include <Sennet/ZED/Recorder.hpp>

#include <Sennet/ZED/Conversion.hpp>

namespace Sennet
{

namespace ZED
{

Recorder::Recorder()
	: m_InitParameters(::Sennet::CreateRef<sl::InitParameters>()),
	m_RecordingParameters(::Sennet::CreateRef<sl::RecordingParameters>()),
	m_RuntimeParameters(::Sennet::CreateRef<sl::RuntimeParameters>()),
	m_Camera(::Sennet::CreateScope<sl::Camera>()),
	m_Running(false),
	m_Recording(false),
	m_Mutex(::Sennet::CreateScope<std::mutex>()),
	m_ExecutionThread(),
	m_InitTimeout(100),
	m_WorkerTimeout(100),
	m_RecordTimeout(10)
{
	Init();
}

Recorder::~Recorder()
{
	Shutdown();
}

void Recorder::Init()
{
	if (m_Running)
	{
		SN_CORE_WARN("[{0}] Already initialized.", GetName());
		return;
	}
	else if (not m_Running and m_Recording)
	{
		SN_CORE_ERROR("[{0}] Critical situation! Forcing \
			shutdown and re-initialization.", GetName());
	}
	else if (not m_Running and not m_Recording)
	{
		SN_CORE_INFO("[{0}] Starting initialization.", GetName());
	}

	StopExecutionThread();
	JoinExecutionThread();
	StartExecutionThread();

	// Sleep a bit to allow the execution thread to start up.
	std::this_thread::sleep_for(m_InitTimeout);
}

void Recorder::Shutdown()
{
	if (not m_Running and not m_Recording)
	{
		SN_CORE_WARN("[{0}] Already shut down.", GetName());
	}
	else if (not m_Running and m_Recording)
	{
		SN_CORE_ERROR("[{0}] Critical situation! Forcing shutdown.",
			GetName());
	}
	else if (m_Running and not m_Recording)
	{
		SN_CORE_INFO("[{0}] Starting shutdown.", GetName());
	}

	StopExecutionThread();
	JoinExecutionThread();
}

std::string Recorder::ToString() const
{
	// TODO: Implement.
	return std::string("");
}

void Recorder::StartRecord()
{
	if (not m_Running)
	{
		SN_CORE_INFO("[{0}] Not initialized, cannot record.",
			GetName());
	}
	else if (m_Running and m_Recording)
	{
		SN_CORE_INFO("[{0}] Already recording.", GetName());
		m_ShouldRecord = true;
	}
	else if (m_Running and not m_Recording)
	{
		SN_CORE_INFO("[{0}] Starting record.", GetName());
		m_ShouldRecord = true;
	}
}

void Recorder::StopRecord()
{
	if (m_Running and not m_Recording)
	{
		SN_CORE_INFO("[{0}] Not recording.", GetName());
	}
	else if (m_Running and m_Recording)
	{
		SN_CORE_INFO("[{0}] Stopping record.", GetName());
	}
	m_ShouldRecord = false;
}

bool Recorder::IsCameraOpened() const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	return m_Camera->isOpened();
}

::Sennet::Ref<image> Recorder::GetImage(const ZED::view& view) const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	if (m_Camera->isOpened())
	{
		auto m = CreateRef<sl::Mat>();
		m_Camera->retrieveImage(*m, ::SennetToStereolabs(view));
		return ::StereolabsToSennet(m);
	}
	else
	{
		return nullptr;
	}
}

::Sennet::Ref<init_params> Recorder::GetInitParameters() const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	return ::StereolabsToSennet(m_InitParameters);
}

::Sennet::Ref<recording_params> Recorder::GetRecordingParameters() const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	return ::StereolabsToSennet(m_RecordingParameters);
}

::Sennet::Ref<runtime_params> Recorder::GetRuntimeParameters() const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	return ::StereolabsToSennet(m_RuntimeParameters);
}

::Sennet::Ref<init_params> Recorder::GetZEDInitParameters() const
{
	if (not IsCameraOpened())
	{
		SN_CORE_WARN("[{0}] ZED is closed.", GetName());
		return nullptr;
	}
	else
	{
		m_Mutex->lock();
		auto params = CreateRef<sl::InitParameters>(
			m_Camera->getInitParameters());
		m_Mutex->unlock();
		return ::StereolabsToSennet(params);
	}
}

Ref<ZED::recording_params> Recorder::GetZEDRecordingParameters() const
{
	if (not IsCameraOpened())
	{
		SN_CORE_WARN("[{0}] ZED is closed.", GetName());
		return nullptr;
	}
	else
	{
		m_Mutex->lock();
		auto recordingParameters = CreateRef<sl::RecordingParameters>(
			m_Camera->getRecordingParameters());
		m_Mutex->unlock();
		return ::StereolabsToSennet(recordingParameters);
	}
}

Ref<ZED::runtime_params> Recorder::GetZEDRuntimeParameters() const
{
	if (not IsCameraOpened())
	{
		SN_CORE_WARN("[{0}] ZED is closed.", GetName());
		return nullptr;
	}
	else
	{
		m_Mutex->lock();
		auto runtimeParameters = CreateRef<sl::RuntimeParameters>(
			m_Camera->getRuntimeParameters());
		m_Mutex->unlock();
		return ::StereolabsToSennet(runtimeParameters);
	}
}

void Recorder::SetInitParameters(const Ref<ZED::init_params> init_params)
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	m_InitParameters = ::SennetToStereolabs(init_params);
}

void Recorder::SetRecordingParameters(const Ref<ZED::recording_params> rec_params)
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	m_RecordingParameters = ::SennetToStereolabs(rec_params);
}

void Recorder::SetRuntimeParameters(const Ref<ZED::runtime_params> run_params)
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	m_RuntimeParameters = ::SennetToStereolabs(run_params);
}

void Recorder::ExecutionWorker()
{
	m_Running = true;
	SN_CORE_INFO("[{0}] Execution worker started.", GetName());
	while (m_ShouldRun)
	{
		if (m_ShouldRecord)
		{
			RecordLoop();
		}
		std::this_thread::sleep_for(m_WorkerTimeout);
	}
	SN_CORE_INFO("[{0}] Execution worker finished.", GetName());
	m_Running = false;
}

void Recorder::RecordLoop()
{
	m_Recording = true;
	SN_CORE_INFO("[{0}] Record loop started.", GetName());

	m_Mutex->lock();
	auto openError = m_Camera->open(*m_InitParameters);
	m_Mutex->unlock();
	if (openError != sl::ERROR_CODE::SUCCESS)
	{
		SN_CORE_WARN("[{0}] Could not open ZED!", GetName());
	}
	else
	{
		SN_CORE_INFO("[{0}] ZED opened.", GetName());
	}

	m_Mutex->lock();
	auto recordError = m_Camera->enableRecording(*m_RecordingParameters);
	m_Mutex->unlock();
	if (recordError != sl::ERROR_CODE::SUCCESS)
	{
		SN_CORE_WARN("[{0}] ZED couldn't enable recording!", GetName());
	}
	else
	{
		SN_CORE_INFO("[{0}] ZED recording enabled.", GetName());
	}

	sl::ERROR_CODE grabError;
	SN_CORE_INFO("[{0}] ZED recording.", GetName());
	while (m_ShouldRecord)
	{
		m_Mutex->lock();
		grabError = m_Camera->grab(*m_RuntimeParameters);
		m_Mutex->unlock();
		if (grabError != sl::ERROR_CODE::SUCCESS)
		{
			SN_CORE_WARN("[{0}] ZED grab failed!", GetName());
		}

		std::this_thread::sleep_for(m_RecordTimeout);
	}

	m_Mutex->lock();
	m_Camera->close();
	m_Mutex->unlock();

	SN_CORE_INFO("[{0}] Record loop finished.", GetName());
	m_Recording = false;
}

void Recorder::StartExecutionThread()
{
	m_ShouldRun = true;
	m_ExecutionThread = ::Sennet::CreateScope<std::thread>(
		&Recorder::ExecutionWorker, this);
}

void Recorder::StopExecutionThread()
{
	StopRecord();
	m_ShouldRun = false;
}

void Recorder::JoinExecutionThread()
{
	if (not m_ExecutionThread)
	{
		return;
	}
	else if (m_ExecutionThread->joinable())
	{
		m_ExecutionThread->join();
		SN_CORE_INFO("[{0}] Joined execution thread.", 
			GetName());
	}
}

}
}

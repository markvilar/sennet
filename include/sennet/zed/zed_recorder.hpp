#pragma once

#include <sennet/snpch.hpp>

#include <sl/Camera.hpp>

#include <sennet/sennet.hpp>

namespace sennet
{

class zed_recorder : public source_handle
{
	// Handle for recording with a ZED camera. The ZED camera is operated
	// in a separate execution thread. The handle public member functions
	// interact with the sensor in a thread safe manner. Additionally, all
	// returned data types are POD or sennet types in order to make the 
	// communication layer independent of the Stereolabs SDK.

public:
	// Source handle member functions.
	zed_recorder();
	~zed_recorder();

	void init() override;
	void shutdown() override;

	SOURCE_HANDLE_CLASS_TYPE(zed_recorder);

	std::string to_string() const override;

	// ZED recorder specific member functions.
	void start_record();
	void stop_record();

	bool is_running() const { return m_running.load(); }
	bool is_recording() const { return m_recording.load(); }
	bool is_zed_opened();

	ref<zed::image> get_image(const zed::view& view=zed::view::left) const;
	ref<zed::init_params> get_init_params() const;
	ref<zed::recording_params> get_rec_params() const;
	ref<zed::runtime_params> get_run_params() const;

	void set_init_params(const ref<zed::init_params> init_params);
	void set_rec_params(const ref<zed::recording_params> rec_params);
	void set_run_params(const ref<zed::runtime_params> run_params);

private:
	void exec_worker();
	void record_loop();

private:
	ref<sl::InitParameters> m_init_params;
	ref<sl::RecordingParameters> m_rec_params;
	ref<sl::RuntimeParameters> m_run_params;

	scope<sl::Camera> m_zed;

	std::atomic<bool> m_running;
	std::atomic<bool> m_recording;
	
	scope<std::mutex> m_mutex;
	scope<std::thread> m_exec_thread;

	std::chrono::milliseconds m_worker_timeout;
	std::chrono::milliseconds m_record_timeout;
};

}

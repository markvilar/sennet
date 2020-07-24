#pragma once

#include <sennet/snpch.hpp>

#include <sl/Camera.hpp>

#include <sennet/sennet.hpp>

namespace sennet
{

namespace zed
{

class recorder : public source_handle
{
	// Handle for recording with a ZED camera. The ZED camera is operated
	// in a separate execution thread. The handle public member functions
	// interact with the sensor in a thread safe manner. Additionally, all
	// returned data types are POD or sennet types in order to make the 
	// communication layer independent of the Stereolabs SDK.

public:
	// Source handle member functions.
	recorder();
	~recorder();

	void init() override;
	void shutdown() override;

	SOURCE_HANDLE_CLASS_TYPE(zed_recorder);

	std::string to_string() const override;

	// ZED recorder specific member functions.
	void start_record();
	void stop_record();

	bool is_running() const { return m_running; }
	bool is_recording() const { return m_recording; }
	bool is_zed_opened() const;

	::sennet::ref<image> get_image(const view& view=view::left) const;
	::sennet::ref<init_params> get_init_params() const;
	::sennet::ref<recording_params> get_rec_params() const;
	::sennet::ref<runtime_params> get_run_params() const;

	::sennet::ref<init_params> get_zed_init_params() const;
	::sennet::ref<recording_params> get_zed_rec_params() const;
	::sennet::ref<runtime_params> get_zed_run_params() const;

	void set_init_params(const ::sennet::ref<init_params> init_params);
	void set_rec_params(const ::sennet::ref<recording_params> rec_params);
	void set_run_params(const ::sennet::ref<runtime_params> run_params);

private:
	void exec_worker();
	void record_loop();

	void start_exec_thread();
	void stop_exec_thread();
	void join_exec_thread();

private:
	// Sensor members.
	::sennet::ref<sl::InitParameters> m_init_params;
	::sennet::ref<sl::RecordingParameters> m_rec_params;
	::sennet::ref<sl::RuntimeParameters> m_run_params;
	::sennet::scope<sl::Camera> m_zed;

	// Thread members.
	::sennet::scope<std::mutex> m_mutex;
	::sennet::scope<std::thread> m_exec_thread;
	std::chrono::milliseconds m_init_timeout;
	std::chrono::milliseconds m_worker_timeout;
	std::chrono::milliseconds m_record_timeout;

	// Status flags.
	std::atomic<bool> m_running;
	std::atomic<bool> m_recording;

	// Command flags.
	std::atomic<bool> m_should_run;
	std::atomic<bool> m_should_record;
};

}

}

#pragma once

#include <sl/Camera.hpp>

#include <sennet/sennet.hpp>

namespace sennet
{

namespace zed
{
enum class state { none = 0, opened, closed, recording };
}

class zed_recorder : public handler
{
	// Handler for recording with a ZED camera. The ZED camera is operated
	// in a separate execution thread. The handler public member functions
	// interact with the sensor in a thread safe manner. Additionally, all
	// returned data types are POD in order to make the communication layer
	// independent of the Stereolabs SDK.
public:
	// Basic handler member functions.
	zed_recorder();
	~zed_recorder();
	void open() override;
	void close() override;
	bool is_opened() const override;
	HANDLER_CLASS_TYPE(zed_recorder);

	// Handler specific member functions.
	std::string to_string() const override;
	void run();
	void stop();

	// ZED specific member functions.
	bool is_zed_opened();
	zed::image get_image() const;
	zed::state get_state() const;
	zed::init_params get_init_params() const;
	zed::recording_params get_rec_params() const;
	zed::runtime_params get_run_params() const;
	void set_init_params(const zed::init_params& init_params);
	void set_rec_params(const zed::recording_params& rec_params);
	void set_run_params(const zed::runtime_params& run_params);

private:
	void exec_worker();
	void run_loop();

private:
	sl::InitParameters m_init_params;
	sl::RecordingParameters m_rec_params;
	sl::RuntimeParameters m_run_params;
	sl::Camera m_zed;

	std::atomic<bool> m_close_flag;
	std::atomic<bool> m_stop_flag;

	std::mutex m_mutex;
	std::thread m_exec_thread;
};

};

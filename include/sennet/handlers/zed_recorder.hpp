#pragma once

#include <sl/Camera.hpp>

#include <sennet/handlers/handler.hpp>

namespace sennet
{

class zed_recorder : public handler
{
public:
	zed_recorder();

	~zed_recorder();

	void virtual open() override;

	void virtual close() override;

	HANDLER_CLASS_TYPE(zed_recorder);

	// std::string to_string() const override;

	// bool is_opened() const override;

	void run();

	void stop();

	void get_image() const;

	void get_status() const;

	void get_settings() const;

	void set_settings();

private:
	void exec_loop();

private:
	sl::InitParameters m_init_params;
	sl::RecordingParameters m_rec_params;
	sl::RuntimeParameters m_run_params;

	std::mutex m_mutex;
	std::thread m_exec_thread;

};

};

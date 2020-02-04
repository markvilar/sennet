#include <zedutils/ZEDio.hpp>

#include <sl/Camera.hpp>

#include <iostream>
#include <string>

class ZEDController
{
	private:
		sl::Camera* camera;
		sl::InitParameters init_params;
		sl::RuntimeParameters run_params;
		sl::RecordingParameters rec_params;
		std::string dir_path;
		unsigned int m_ID;
	public:
		ZEDController(const std::string path);
		~ZEDController();

		// Attribute functions
		inline std::string get_path() const { return dir_path; }
		inline void set_path(const std::string path) { dir_path = path; }
		inline unsigned int get_id() const { return m_ID; }
		
		// Camera - Controls
		bool is_camera_bounded() const;
		bool is_camera_opened() const;
		void bind_camera(sl::Camera* camera);
		void unbind_camera();
		sl::ERROR_CODE open_camera(const sl::InitParameters param) const;
		void close_camera() const;

		// Camera - Information
		sl::InitParameters get_init_parameters() const;
		sl::RuntimeParameters get_runtime_parameters() const;
		sl::CameraInformation get_camera_info() const;
		
		// Camera - Video settings
		void set_camera_settings(sl::VIDEO_SETTINGS settings, int value) 
			const;
		int get_camera_settings(sl::VIDEO_SETTINGS settings) const;
		float get_camera_fps() const;

		// Camera - Recording
		sl::ERROR_CODE enable_camera_recording(
				sl::RecordingParameters params) const;
		void disable_camera_recording() const;
		bool is_camera_recording() const;
		bool is_camera_paused() const;
		void pause_camera_recording() const;
		void resume_camera_recording() const;
		sl::ERROR_CODE camera_record(sl::RuntimeParameters params, 
				unsigned int count) const;
		sl::RecordingStatus get_camera_recording_status() const;
		sl::RecordingParameters get_camera_recording_parameters() const;

		// Miscellaneous
		friend std::ostream& operator<<(std::ostream& os, 
				const ZEDController& ctrl);
};

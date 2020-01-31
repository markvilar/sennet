#include <zedutils/ZEDio.hpp>

#include <sl/Camera.hpp>

class ZEDController
{
	private:
		sl::Camera* camera;
		unsigned int m_ID;
	public:
		ZEDController();
		~ZEDController();

		// Misc.
		inline unsigned int get_id() const { return m_ID; }
		friend std::ostream& operator<<(std::ostream& os, 
				const ZEDController& ctrl);
		
		// Camera controls
		bool camera_bounded() const;
		bool camera_opened() const;
		void bind_camera(sl::Camera* camera);
		void unbind_camera();
		sl::ERROR_CODE open_camera(const sl::InitParameters param) const;
		void close_camera() const;

		// Retrieve camera information
		sl::InitParameters get_init_parameters() const;
		sl::RuntimeParameters get_runtime_parameters() const;
		sl::CameraInformation get_camera_info() const;
		
		// Video settings
		bool set_camera_settings(sl::VIDEO_SETTINGS settings);
		int get_camera_settings(sl::VIDEO_SETTINGS settings) const;

		// Recording
		
};

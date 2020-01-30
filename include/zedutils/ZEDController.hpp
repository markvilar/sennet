#include <zedutils/ZEDio.hpp>

#include <sl/Camera.hpp>

class ZEDController
{
	private:
		sl::Camera* camera;
	public:
		ZEDController();
		~ZEDController();
		
		bool has_camera_bounded();
		void bind(sl::Camera* camera);
		void unbind();
		
		bool is_camera_open();
		sl::ERROR_CODE open_camera();
		sl::ERROR_CODE close_camera();
};

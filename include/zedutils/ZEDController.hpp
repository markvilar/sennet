#include <zedutils/zederrors.hpp>

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
};

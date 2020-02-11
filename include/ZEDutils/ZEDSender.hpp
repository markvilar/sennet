#include <sl/Camera.hpp>

#include <ZEDutils/ZEDio.hpp>

class ZEDSender
{
	private:
		sl::StreamingParameters stream_params;
	public:
		ZEDSender(sl::StreamingParameters params);
		~ZEDSender();
		sl::ERROR_CODE stream(sl::Camera& cam) const;
		sl::ERROR_CODE stream(sl::Camera& cam, const sl::StreamingParameters stream_params) const;
};

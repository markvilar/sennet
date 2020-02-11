#include <ZEDutils/ZEDSender.hpp>

ZEDSender::ZEDSender(sl::StreamingParameters params) : stream_params(params)
{
}


ZEDSender::~ZEDSender()
{
}


sl::ERROR_CODE ZEDSender::stream(sl::Camera& cam) const
{
	return stream(cam, stream_params);
}


sl::ERROR_CODE ZEDSender::stream(sl::Camera& cam, 
		sl::StreamingParameters stream_params) const
{
	sl::ERROR_CODE error = cam.enableStreaming(stream_params);
	if (error != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << "Stream initialization failed!" << std::endl;
		return error;
	}

	// Stream printout
	std::cout << "Streaming on port " << std::to_string(stream_params.port) 
		<< " with bitrate " << std::to_string(stream_params.bitrate) 
		<< std::endl;

	// Stream loop
	unsigned int frame_count = 0;
	unsigned int max_count = 10000;
	error = sl::ERROR_CODE::SUCCESS;
	while(frame_count < max_count)
	{
		if(cam.grab() == sl::ERROR_CODE::SUCCESS)
		{
			frame_count++;
		}
		else
		{
			sl::sleep_ms(1);
		}
	}
	
	cam.disableStreaming();
	return sl::ERROR_CODE::SUCCESS;
}

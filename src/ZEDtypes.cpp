#include <ZEDutils/ZEDtypes.hpp>

sl::Mat flattenMat(sl::Mat& x)
{
	if(x.getMemoryType() != sl::MEM::CPU)
	{
		auto error = x.updateCPUfromGPU();
		if(error != sl::ERROR_CODE::SUCCESS)
		{
			throw "sl::Mat: Transfer from GPU to CPU error";
		}
	}
	size_t w = x.getWidth();
	size_t h = x.getHeight();
	size_t c = x.getChannels();
	return sl::Mat();
}

std::vector<boost::uint8_t> slMat2Vec(sl::Mat& x)
{
	size_t rows = x.getHeight();
	size_t cols = x.getWidth();
	size_t size = x.getPixelBytes();
	
	std::vector<boost::uint8_t> vec;
	auto data = x.getPtr<boost::uint8_t>(sl::MEM::CPU);
	
	return std::vector<boost::uint8_t>(data, 
		data + rows*cols*(size/sizeof(boost::uint8_t)));
}

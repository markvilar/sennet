#include <sennet/types/zed.hpp>

namespace sennet
{

namespace zed
{

image::image()
	: m_buffer(),
	m_width(0),
	m_height(0),
	m_channels(0)
{
}

image::image(const unsigned char* ptr, const size_t width, const size_t height,
	const size_t channels)
{
	m_buffer.assign(ptr, ptr + width*height*channels);
	m_width = width;
	m_height = height;
	m_channels = channels;
}

image::image(const image& other)
	: m_buffer(other.get_buffer()),
	m_width(other.get_width()), 
	m_height(other.get_height()),
	m_channels(other.get_channels())
{
	// TODO: Debug this to make sure it copies correctly.
}

image::~image()
{
}

unsigned char image::get_pixel(const size_t col, const size_t row, 
	const size_t channel) const
{
	try
	{
		size_t width = get_width();
		size_t height = get_height();
		size_t channels = get_channels();
		if (col >= width)
		{
			throw std::out_of_range("zed::image : width of out range");
		}
		else if (row >= height)
		{
			throw std::out_of_range("zed::image : heigth of out range");
		}
		else if (channel >= channels)
		{
			throw std::out_of_range("zed::image : channel of out range");
		}
		else
		{
			return m_buffer[col*channels+row*width*channels+channel];
		}
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << oor.what() << "\n";
		return 0;
	}
}

void image::set_pixel(const size_t col, const size_t row, 
	const size_t channel, const unsigned char value)
{
	try
	{
		size_t width = get_width();
		size_t height = get_height();
		size_t channels = get_channels();
		if (col >= width)
		{
			throw std::out_of_range("zed::image : width of out range");
		}
		else if (row >= height)
		{
			throw std::out_of_range("zed::image : heigth of out range");
		}
		else if (channel >= channels)
		{
			throw std::out_of_range("zed::image : channel of out range");
		}
		else
		{
			m_buffer[col*channels+row*width*channels+channel] = value;
		}
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << oor.what() << "\n";
	}
}

std::string image::to_string() const
{
	std::stringstream ss;
	ss << "[zed::image] " << static_cast<const void*>(get_ptr()) << ", (" 
		<< get_width() << "," << get_height() << "," << get_channels() 
		<< "), size: " << get_size();
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const image& img)
{
	os << img.to_string();
	return os;
}

}
};

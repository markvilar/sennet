#include "Sennet/Primitives/Image.hpp"

namespace Sennet
{

Image::Image()
	: m_Buffer(),
	m_Width(0),
	m_Height(0),
	m_Channels(0)
{
}

Image::Image(const std::vector<unsigned char> data, const size_t width, 
	const size_t height, const size_t channels)
	: m_Buffer(data), m_Width(width), m_Height(height), m_Channels(channels)
{
}

Image::Image(const unsigned char* ptr, const size_t width, const size_t height,
	const size_t channels)
{
	m_Buffer.assign(ptr, ptr + width*height*channels);
	m_Width = width;
	m_Height = height;
	m_Channels = channels;
}

Image::Image(const Image& other)
	: m_Buffer(other.GetBuffer()),
	m_Width(other.GetWidth()), 
	m_Height(other.GetHeight()),
	m_Channels(other.GetChannels())
{
	// TODO: Debug this to make sure it copies correctly.
}

Image::~Image()
{
}

unsigned char Image::GetPixel(const size_t col, const size_t row, 
	const size_t channel) const
{
	SN_CORE_ASSERT(col < m_Width, "[Image] Coloumn out of range.");
	SN_CORE_ASSERT(row < m_Height, "[Image] Row out of range.");
	SN_CORE_ASSERT(channel < m_Channels, "[Image] Channel out of range.");

	return m_Buffer[col*m_Channels + row*m_Width*m_Channels + channel];
}

void Image::SetPixel(const size_t col, const size_t row, const size_t channel,
	const unsigned char value)
{
	SN_CORE_ASSERT(col < m_Width, "[Image] Coloumn out of range.");
	SN_CORE_ASSERT(row < m_Height, "[Image] Row out of range.");
	SN_CORE_ASSERT(channel < m_Channels, "[Image] Channel out of range.");

	m_Buffer[col*m_Channels + row*m_Width*m_Channels + channel] = value;
}

std::string Image::ToString() const
{
	std::stringstream ss;
	ss << "[Image] " << static_cast<const void*>(GetPtr()) << ", "
		<< GetSize() << " (" << GetWidth() << "," << GetHeight()
		 << "," << GetChannels() << ")";
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Image& image)
{
	return os << image.ToString();
}

}

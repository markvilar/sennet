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

Image::Image(const std::vector<uint8_t>& data, const uint32_t& width, 
	const uint32_t& height, const uint32_t& channels)
	: m_Buffer(data), m_Width(width), m_Height(height), m_Channels(channels)
{
}

Image::Image(const uint8_t* ptr, const uint32_t& width, const uint32_t& height,
	const uint32_t& channels)
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

unsigned char Image::GetPixel(const uint32_t& col, const uint32_t& row, 
	const uint32_t& channel) const
{
	SN_CORE_ASSERT(col < m_Width, "[Image] Coloumn out of range.");
	SN_CORE_ASSERT(row < m_Height, "[Image] Row out of range.");
	SN_CORE_ASSERT(channel < m_Channels, "[Image] Channel out of range.");

	return m_Buffer[col*m_Channels + row*m_Width*m_Channels + channel];
}

void Image::SetPixel(const uint32_t& col, const uint32_t& row, 
	const uint32_t& channel, const uint8_t& value)
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

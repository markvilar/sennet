#include <Sennet/Messages/ImageMessage.hpp>

namespace Sennet
{

ImageMessage::ImageMessage()
	: m_Buffer(), m_Width(0), m_Height(0), m_Channels(0)
{
}

ImageMessage::ImageMessage(const std::vector<unsigned char>& buffer,
	const size_t width, const size_t height, const size_t channels)
	: m_Buffer(buffer), m_Width(width), m_Height(height),
	m_Channels(channels)
{
}

MessageType ImageMessage::GetMessageType() const
{
	return MessageType::ImageMessage;
}

const char* ImageMessage::GetName() const
{
	return "ImageMessage";
}

std::string ImageMessage::ToString() const
{
	std::stringstream ss;
	ss << GetName() << ": " << m_Buffer.size() << ", (" << m_Width << ", " 
		<< m_Height << ", " << m_Channels << ")";
	return ss.str();
}

Message* ImageMessage::Clone() const 
{
	return new ImageMessage(m_Buffer, m_Width, m_Height, m_Channels);
}

}

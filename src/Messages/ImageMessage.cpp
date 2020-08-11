#include <Sennet/Messages/ImageMessage.hpp>

namespace Sennet
{

ImageMessage::ImageMessage()
	: m_Image()
{
}

ImageMessage::ImageMessage(const Image& image)
	: m_Image(image)
{
}

MessageType ImageMessage::GetStaticType()
{
	return MessageType::ImageMessage;
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
	ss << GetName() << ": " << m_Image.ToString();
	return ss.str();
}

}

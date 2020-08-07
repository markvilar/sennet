#include <Sennet/Messages/HelloMessage.hpp>

namespace Sennet
{

MessageType HelloMessage::GetMessageType() const
{
	return MessageType::HelloMessage;
}

const char* HelloMessage::GetName() const
{
	return "HelloMessage";
}

std::string HelloMessage::ToString() const
{
	return std::string(GetName()) + ": " + m_Greeting;
}

Message* HelloMessage::Clone() const
{
	return new HelloMessage(m_Greeting);
}

}

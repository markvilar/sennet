#include "Sennet/Messages/BasicMessage.hpp"

namespace Sennet
{

std::string TextMessage::ToString() const
{ 
	std::stringstream ss;
	ss << GetName() << ": " << m_Text;
	return ss.str();
}

std::string ImageMessage::ToString() const
{
	std::stringstream ss;
	ss << GetName() << ": " << m_Image.ToString();
	return ss.str();
}

}

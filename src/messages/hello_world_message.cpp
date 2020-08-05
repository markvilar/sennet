#include <sennet/messages/hello_world_message.hpp>

namespace sennet
{

message_type hello_world_message::get_message_type() const
{
	return message_type::hello_world_message;
}

const char* hello_world_message::get_name() const
{
	return "hello_world_message";
}

std::string hello_world_message::to_string() const
{
	return std::string(get_name()) + ": " + m_greeting;
}

message* hello_world_message::clone() const
{
	return new hello_world_message(m_greeting);
}

}

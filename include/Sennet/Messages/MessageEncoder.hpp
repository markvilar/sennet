#pragma once
#include <Sennet/pch.hpp>

#include <Sennet/Messages/Message.hpp>

namespace Sennet
{

class MessageEncoder
{
public:
	static Ref<MessageEncoding> Encode(const Ref<Message>& msg);
	static Ref<Message> Decode(const Ref<MessageEncoding>& rawMsg);
};

}

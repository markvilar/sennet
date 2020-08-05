#pragma once
#include <sennet/pch.hpp>

#include <sennet/messages/message.hpp>

namespace sennet
{

class message_encoder
{
public:
	static ref<message_encoding> encode(const ref<message>& msg);
	static ref<message> decode(const ref<message_encoding>& raw_msg);
};

}

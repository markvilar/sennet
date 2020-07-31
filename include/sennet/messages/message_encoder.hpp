#pragma once
#include <sennet/snpch.hpp>

#include <sennet/messages/message.hpp>

namespace sennet
{

class message_encoder
{
public:
	static std::vector<char>* encode(const message& msg);
	static message* decode(std::vector<char>& raw_msg);
};

}

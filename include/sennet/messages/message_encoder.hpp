#pragma once
#include <sennet/snpch.hpp>

#include <sennet/messages/message.hpp>

namespace sennet
{

class message_encoder
{
public:
	static std::string* encode(const message& msg);
	static message* decode(const std::string& raw_msg);
};

message* type_to_class(const message_type& type);

}

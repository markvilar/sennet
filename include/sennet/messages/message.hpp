#pragma once
#include <sennet/snpch.hpp>

#include <serializer/serializer.h>

namespace sennet
{

using message_encoding = std::vector<unsigned char>;

enum class message_type
{
	none = 0,
	message,
	hello_world_message
};

class message : public zpp::serializer::polymorphic
{
	// Interface class for messages sent over the network.
public:
	virtual ~message() = default;

	virtual message_type get_message_type() const = 0;
	virtual const char* get_name() const = 0;
	virtual std::string to_string() const = 0;
	virtual message* clone() const = 0;
};

}

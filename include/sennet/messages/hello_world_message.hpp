#pragma once

#include <sennet/messages/message.hpp>

namespace sennet
{

class hello_world_message : public message
{
public:
	hello_world_message() = default;
	virtual ~hello_world_message() = default;

	virtual message_type get_message_type() const override
	{
		return message_type::hello_world_message;
	}

	virtual const char* get_name() const override { return "message"; }
	virtual std::string to_string() const override { return get_name(); }
	virtual message* clone() const override
	{
		return new hello_world_message();
	}

private:
	NOP_STRUCTURE(hello_world_message);
};

}

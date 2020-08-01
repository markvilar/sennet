#pragma once
#include <sennet/snpch.hpp>

#include <nop/structure.h>

namespace sennet
{

enum class message_type
{
	none = 0,
	message,
	hello_world_message
};


struct message_parcel
{
public:
	message_type m_type;
	std::vector<char> m_encoded_message;

private:
	NOP_STRUCTURE(message_parcel, m_type, m_encoded_message);
};

class message
{
public:
	message() = default;
	virtual ~message() = default;

	virtual message_type get_message_type() const 
	{ 
		return message_type::message;
	}

	virtual const char* get_name() const { return "message"; }
	virtual std::string to_string() const { return get_name(); }
	virtual message* clone() const { return new message(); }

private:
	NOP_STRUCTURE(message);
};

}

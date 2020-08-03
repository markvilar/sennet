#pragma once
#include <sennet/snpch.hpp>

#include <nop/structure.h>

namespace sennet
{

enum class message_type
{
	none = 0,
	message,
	hello_world_message,
};


struct message_header
{
	// Table to store the information needed to recreate message objects
	// from a parcel stream.
public:
	message_type m_type;
	std::string m_message;

private:
	NOP_STRUCTURE(message_header, m_type, m_message);
};

class message
{
public:
	message() = default;
	message(const std::string& text) : m_text(text) {}
	virtual ~message() = default;

	virtual message_type get_message_type() const 
	{ 
		return message_type::message;
	}

	virtual const char* get_name() const { return "message"; }
	virtual std::string to_string() const { return "message: " + m_text; }
	virtual message* clone() const { return new message(); }

protected:
	std::string m_text;

private:
	NOP_STRUCTURE(message, m_text);
};

}

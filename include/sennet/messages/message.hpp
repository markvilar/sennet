#pragma once
#include <sennet/snpch.hpp>



namespace sennet
{

enum class message_type
{
	none = 0,
	message,
	hello_world
};

struct message
{
public:
	message_type m_type;
	message* clone() const { return nullptr; }
};

}

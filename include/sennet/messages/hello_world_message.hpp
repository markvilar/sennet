#pragma once
#include <sennet/snpch.hpp>

#include <sennet/messages/message.hpp>

namespace sennet
{

class hello_world_message : public message
{
public:
	hello_world_message() = default;
	hello_world_message(const std::string& greeting) 
		: m_greeting(greeting) {}
	virtual ~hello_world_message() = default;

	virtual message_type get_message_type() const override;
	virtual const char* get_name() const override;
	virtual std::string to_string() const override;
	virtual message* clone() const override;

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_greeting);
	}

private:
	std::string m_greeting;
};

}

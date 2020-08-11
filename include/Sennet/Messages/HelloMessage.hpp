#pragma once
#include <Sennet/pch.hpp>

#include <Sennet/Messages/Message.hpp>

namespace Sennet
{

class HelloMessage: public Message
{
public:
	HelloMessage() = default;
	HelloMessage(const std::string& greeting) : m_Greeting(greeting) {}
	virtual ~HelloMessage() = default;

	static MessageType GetStaticType();
	virtual MessageType GetMessageType() const override;
	virtual const char* GetName() const override;
	virtual std::string ToString() const override;

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_Greeting);
	}

private:
	std::string m_Greeting;
};

}

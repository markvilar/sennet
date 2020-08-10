#pragma once
#include <Sennet/pch.hpp>

#include <serializer/serializer.h>

namespace Sennet
{

using MessageEncoding = std::vector<unsigned char>;

enum class MessageType
{
	None 		= 0,
	HelloMessage 	= 1,
	ImageMessage 	= 2,
	NodeMessage	= 3,
	ZEDMessage	= 4
};

class Message : public zpp::serializer::polymorphic
{
	// Interface class for messages sent over the network.
public:
	virtual ~Message() = default;

	virtual MessageType GetMessageType() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const = 0;
};

class MessageEncoder
{
public:
	static Ref<MessageEncoding> Encode(const Ref<Message>& msg);
	static Ref<Message> Decode(const Ref<MessageEncoding>& rawMsg);
};

}

#pragma once

#include <utility>
#include <vector>
#include <string>

#include <serializer/serializer.h>

namespace Sennet
{

using MessageEncoding = std::vector<unsigned char>;

enum class MessageType
{
	None 				= 0,
	TextMessage 			= 1,
	ImageMessage 			= 2,
	ZEDCommandRequest 		= 3,
	ZEDSettingsRequest		= 4,
	ZEDStateRequest			= 5,
	ZEDCommandResponse		= 6,
	ZEDSettingsResponse		= 7,
	ZEDStateResponse		= 8
};

#define MESSAGE_CLASS_TYPE(type) 					\
	static MessageType GetStaticType()				\
	{ return MessageType::type; }					\
	virtual MessageType GetMessageType() const override		\
	{ return GetStaticType(); }					\
	virtual const char* GetName() const override 			\
	{ return #type; }						


class Message : public zpp::serializer::polymorphic
{
	// Interface class for messages sent over the network.
public:
	virtual ~Message() = default;

	virtual MessageType GetMessageType() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const = 0;

public:
	bool Handled = false;
};

class Request : public Message
{
public:
	Request() = default;
	Request(const std::string address, const unsigned short port)
		: m_SenderAddress(address), m_SenderPort(port) {}
	virtual ~Request() = default;

	std::pair<std::string, unsigned short> GetSender() 
	{ 
		return { m_SenderAddress, m_SenderPort };
	}

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_SenderAddress);
		archive(self.m_SenderPort);
	}

private:
	std::string m_SenderAddress;
	unsigned short m_SenderPort;
};

class Response : public Message
{
public:
	Response() = default;
	Response(const std::string address, const unsigned short port)
		: m_SenderAddress(address), m_SenderPort(port) {}
	virtual ~Response() = default;

	std::pair<std::string, unsigned short> GetSender() 
	{ 
		return { m_SenderAddress, m_SenderPort };
	}

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_SenderAddress);
		archive(self.m_SenderPort);
	}

private:
	std::string m_SenderAddress;
	unsigned short m_SenderPort;
};

class MessageDispatcher
{
public:
	MessageDispatcher(Ref<Message> msg)
		: m_Message(msg)
	{
	}

	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Message->GetMessageType() == T::GetStaticType())
		{
			m_Message->Handled = func(std::dynamic_pointer_cast<T>(
				m_Message));
			return true;
		}
		return false;
	}

private:
	Ref<Message> m_Message;
};

class MessageEncoder
{
public:
	static Ref<MessageEncoding> Encode(const Ref<Message>& msg);
	static Ref<Message> Decode(const Ref<MessageEncoding>& rawMsg);
};

}

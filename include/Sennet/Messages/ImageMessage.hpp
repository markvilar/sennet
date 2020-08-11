#pragma once

#include <Sennet/pch.hpp>

#include <Sennet/Messages/Message.hpp>
#include <Sennet/Primitives/Image.hpp>

namespace Sennet
{

class ImageMessage : public Message
{
public:
	ImageMessage();
	ImageMessage(const Image& image);
	virtual ~ImageMessage() = default;

	static MessageType GetStaticType();
	virtual MessageType GetMessageType() const override;
	virtual const char* GetName() const override;
	virtual std::string ToString() const override;

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_Image);
	}

private:
	Image m_Image;
};

}

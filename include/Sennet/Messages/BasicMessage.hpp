#pragma once

#include <Sennet/Messages/Message.hpp>

#include <Sennet/Primitives/Image.hpp>

namespace Sennet
{

class TextMessage : public Response
{
public:
	TextMessage() = default;
	TextMessage(const std::string address, const unsigned short port,
		const std::string text)
		: Response(address, port), m_Text(text) {}
	virtual ~TextMessage() = default;

	MESSAGE_CLASS_TYPE(TextMessage);

	std::string ToString() const override;

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Response::serialize(archive, self);
		archive(self.m_Text);
	}

private:
	std::string m_Text;
};

class ImageMessage : public Response
{
public:
	ImageMessage() = default;
	ImageMessage(const std::string address, const unsigned short port,
		const Image& image)
		: Response(address, port), m_Image(image) {}
	virtual ~ImageMessage() = default;

	MESSAGE_CLASS_TYPE(ImageMessage);

	std::string ToString() const override;

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Response::serialize(archive, self);
		archive(self.m_Image);
	}

private:
	Image m_Image;
};

}

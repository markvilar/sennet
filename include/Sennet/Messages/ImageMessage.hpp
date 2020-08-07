#pragma once

#include <Sennet/pch.hpp>

#include <Sennet/Messages/Message.hpp>
#include <Sennet/Primitives/ZED.hpp>

namespace Sennet
{

class ImageMessage : public Message
{
public:
	ImageMessage();
	ImageMessage(const std::vector<unsigned char>& buffer,
		const size_t width, const size_t height, const size_t channels);
	virtual ~ImageMessage() = default;

	virtual MessageType GetMessageType() const override;
	virtual const char* GetName() const override;
	virtual std::string ToString() const override;
	virtual Message* Clone() const override;

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_Buffer);
		archive(self.m_Width);
		archive(self.m_Height);
		archive(self.m_Channels);
	}

private:
	std::vector<unsigned char> m_Buffer;
	size_t m_Width;
	size_t m_Height;
	size_t m_Channels;
};

}

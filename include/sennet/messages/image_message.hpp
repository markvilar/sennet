#pragma once

#include <sennet/pch.hpp>

#include <sennet/messages/message.hpp>
#include <sennet/types/zed.hpp>

namespace sennet
{

class image_message : public message
{
public:
	image_message();
	image_message(const std::vector<unsigned char>& buffer,
		const size_t width, const size_t height, const size_t channels,
		const zed::view& view);
	virtual ~image_message() = default;

	virtual message_type get_message_type() const override;
	virtual const char* get_name() const override;
	virtual std::string to_string() const override;
	virtual message* clone() const override;

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_buffer);
		archive(self.m_width);
		archive(self.m_height);
		archive(self.m_channels);
		archive(self.m_view);
	}

private:
	std::vector<unsigned char> m_buffer;
	size_t m_width;
	size_t m_height;
	size_t m_channels;
	zed::view m_view;
};

}

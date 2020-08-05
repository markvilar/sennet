#include <sennet/messages/image_message.hpp>

namespace sennet
{

image_message::image_message()
	: m_buffer(), m_width(0), m_height(0), m_channels(0), 
	m_view(zed::view::none)
{
}

image_message::image_message(const std::vector<unsigned char>& buffer,
	const size_t width, const size_t height, const size_t channels,
	const zed::view& view)
	: m_buffer(buffer), m_width(width), m_height(height),
	m_channels(channels), m_view(view)
{
}

message_type image_message::get_message_type() const
{
	return message_type::image_message;
}

const char* image_message::get_name() const
{
	return "image_message";
}

std::string image_message::to_string() const
{
	std::stringstream ss;
	ss << get_name() << ": " << m_buffer.size() << ", (" << m_width << ", " 
		<< m_height << ", " << m_channels << "), " << m_view;
	return ss.str();
}

message* image_message::clone() const 
{
	return new image_message(m_buffer, m_width, m_height, m_channels,
		m_view);
}

}

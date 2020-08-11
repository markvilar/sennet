#pragma once
#include <Sennet/pch.hpp>

#include <serializer/serializer.h>

namespace Sennet
{

class Image
{
	// Wrapper for sl::Mat with unsigned char data. Neglects functionality 
	// of the Stereolabs SDK that is considered unimportant for recording.
public:
	Image();
	Image(const std::vector<unsigned char> data, const size_t width,
		const size_t height, const size_t channels);
	Image(const unsigned char* ptr, const size_t width, const size_t height, 
		const size_t channels);
	Image(const Image& other);
	~Image();

	inline std::vector<unsigned char> GetBuffer() const { return m_Buffer; }
	inline unsigned char* GetPtr() { return m_Buffer.data(); }
	inline const unsigned char* GetPtr() const { return m_Buffer.data(); }
	inline size_t GetWidth() const { return m_Width; }
	inline size_t GetHeight() const { return m_Height; }
	inline size_t GetChannels() const { return m_Channels; }
	inline size_t GetSize() const { return m_Width * m_Height * m_Channels; }

	unsigned char GetPixel(const size_t col, const size_t row, 
		const size_t channel) const;
	void SetPixel(const size_t col, const size_t row, 
		const size_t channel, const unsigned char value);
	void PrintPixel(const size_t w, const size_t h) const;

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, const Image& image);

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

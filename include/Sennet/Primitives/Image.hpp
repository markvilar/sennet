#pragma once
#include "Sennet/pch.hpp"

#include <serializer/serializer.h>

namespace Sennet
{

class Image
{
	// Wrapper for sl::Mat with unsigned char data. Neglects functionality 
	// of the Stereolabs SDK that is considered unimportant for recording.
public:
	Image();
	Image(const std::vector<uint8_t>& data, const uint32_t& width,
		const uint32_t& height, const uint32_t& channels);
	Image(const uint8_t* ptr, const uint32_t& width, 
		const uint32_t& height, const uint32_t& channels);
	Image(const Image& other);
	~Image();

	inline std::vector<uint8_t> GetBuffer() const { return m_Buffer; }
	inline unsigned char* GetPtr() { return m_Buffer.data(); }
	inline const unsigned char* GetPtr() const { return m_Buffer.data(); }
	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }
	inline uint32_t GetChannels() const { return m_Channels; }
	inline uint32_t GetSize() const 
	{ 
		return m_Width * m_Height * m_Channels; 
	}

	unsigned char GetPixel(const uint32_t& col, const uint32_t& row, 
		const uint32_t& channel) const;
	void SetPixel(const uint32_t& col, const uint32_t& row, 
		const uint32_t& channel, const uint8_t& value);
	void PrintPixel(const uint32_t& w, const uint32_t& h) const;

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
	std::vector<uint8_t> m_Buffer;
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_Channels;
};

}

#include "Sennet/pch.hpp"
#include "Sennet/Platform/OpenGL/OpenGLTexture.hpp"

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Sennet
{

GLenum SennetToOpenGL(const Texture::InternalFormat& internalFormat)
{
	GLenum glInternalFormat = 0;
	switch (internalFormat)
	{
		case Texture::InternalFormat::RGBA8:
			glInternalFormat = GL_RGBA8;
			break;
	}
	SN_CORE_ASSERT(glInternalFormat, "Invalid OpenGL internal format.");
	return glInternalFormat;
}

GLenum SennetToOpenGL(const Texture::DataFormat& dataFormat)
{
	GLenum glDataFormat = 0;
	switch (dataFormat)
	{
		case Texture::DataFormat::RGBA:
			glDataFormat = GL_RGBA;
			break;
	}
	SN_CORE_ASSERT(glDataFormat, "Invalid OpenGL data format.");
	return glDataFormat;
}

OpenGLTexture2D::OpenGLTexture2D(const uint32_t& width, const uint32_t& height,
	const InternalFormat internalFormat, const DataFormat dataFormat)
	: m_Source(""), m_Width(width), m_Height(height), 
	m_InternalFormat(internalFormat), m_DataFormat(dataFormat)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, SennetToOpenGL(m_InternalFormat), 
		m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	: m_Source(path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data)
	{
		SN_CORE_ERROR("Could not load texture '{0}'", path);
		SN_CORE_ASSERT(false, "Texture loading failed!");
	}

	m_Width = width;
	m_Height = height;

	auto internalFormat = InternalFormat::None;
	auto dataFormat = DataFormat::None;
	if (channels == 4)
	{
		internalFormat = InternalFormat::RGBA8;
		dataFormat = DataFormat::RGBA;
	}
	else if (channels == 3)
	{
		internalFormat = InternalFormat::RGB8;
		dataFormat = DataFormat::RGB;
	}

	m_InternalFormat = internalFormat;
	m_DataFormat = dataFormat;
	
	SN_CORE_ASSERT(!(internalFormat == InternalFormat::None), 
		"Texture internal format is not supported!");
	SN_CORE_ASSERT(!(dataFormat == DataFormat::None), 
		"Texture data format is not supported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, SennetToOpenGL(m_InternalFormat), 
		m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, 
		SennetToOpenGL(m_DataFormat), GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::SetData(void* data, const uint32_t& size)
{
	uint32_t bpp = m_DataFormat == DataFormat::RGBA ? 4 : 3;
	SN_CORE_ASSERT(size == m_Width * m_Height * bpp, 
		"Data must be entire texture.");
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, 
		SennetToOpenGL(m_DataFormat), GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

void OpenGLTexture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

}

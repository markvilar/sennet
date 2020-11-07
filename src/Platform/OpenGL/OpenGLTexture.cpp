#include "Sennet/pch.hpp"
#include "Sennet/Platform/OpenGL/OpenGLTexture.hpp"

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Sennet
{

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

	GLenum internalFormat = 0, dataFormat = 0;
	if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	SN_CORE_ASSERT(internalFormat & dataFormat, "Texture format is not \
		supported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat,
		GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

OpenGLTexture2D::OpenGLTexture2D(const Image& image)
	: m_Source("Image")
{
	auto data = image.GetPtr();

	if (!data)
	{
		SN_CORE_ERROR("Could not load texture '{0}'", image.ToString());
		SN_CORE_ASSERT(false, "Texture loading failed!");
	}

	m_Width = image.GetWidth();
	m_Height = image.GetHeight();
	uint32_t channels = image.GetChannels();

	GLenum internalFormat = 0, dataFormat = 0;
	if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_BGRA;
	}
	else if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_BGR;
	}

	SN_CORE_ASSERT(internalFormat & dataFormat, "Texture format is not \
		supported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat,
		GL_UNSIGNED_BYTE, data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

}

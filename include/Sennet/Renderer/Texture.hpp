#pragma once

#include <string>

#include "Sennet/Core/Base.hpp"

#include "Sennet/Primitives/Image.hpp"

namespace Sennet
{

class Texture
{
public:
	virtual ~Texture() = default;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;

	virtual uint32_t GetRendererID() const = 0;

	virtual void SetData(void* data, const uint32_t& size) = 0;

	virtual void Bind(uint32_t slot = 0) const = 0;
	virtual void Unbind() const = 0;

};

class Texture2D : public Texture
{
public:
	static Ref<Texture2D> Create(const uint32_t& width, 
		const uint32_t& height);
	static Ref<Texture2D> Create(const std::string& path);
	static Ref<Texture2D> Create(const Image& image);
};

}

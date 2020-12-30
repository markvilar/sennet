#include "Sennet/Pch.hpp"
#include "Sennet/Renderer/Renderer2D.hpp"

#include "Sennet/Renderer/RenderCommand.hpp"
#include "Sennet/Renderer/Shader.hpp"
#include "Sennet/Renderer/VertexArray.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Sennet
{

struct QuadVertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TextureCoord;
    float TextureIndex;
    float TilingFactor;
};

struct Renderer2DData
{
    static const uint32_t MaxQuads = 20000;
    static const uint32_t MaxVertices = MaxQuads 
        * Renderer2D::QuadData::VerticesPerQuad;
    static const uint32_t MaxIndices = MaxQuads 
        * Renderer2D::QuadData::IndicesPerQuad;
    static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

	Ref<VertexArray> QuadVertexArray;
    Ref<VertexBuffer> QuadVertexBuffer;
	Ref<Shader> TextureShader;
	Ref<Texture2D> WhiteTexture;

    uint32_t QuadIndexCount = 0;
    QuadVertex* QuadVertexBufferBase = nullptr;
    QuadVertex* QuadVertexBufferPtr = nullptr;

    std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
    uint32_t TextureSlotIndex = 1; // 0 = white texture

    glm::vec4 QuadVertexPositions[Renderer2D::QuadData::VerticesPerQuad];
    glm::vec2 QuadTextureCoords[Renderer2D::QuadData::VerticesPerQuad];

    Renderer2D::Statistics Stats;
};

static Renderer2DData s_Data;

void Renderer2D::Init()
{
	s_Data.QuadVertexArray = VertexArray::Create();
	
    // Vertex buffer.
	s_Data.QuadVertexBuffer = VertexBuffer::Create(
        s_Data.MaxVertices * sizeof(QuadVertex));

	s_Data.QuadVertexBuffer->SetLayout({
		{ ShaderDataType::Float3, "a_Position"      },
        { ShaderDataType::Float4, "a_Color"         },
		{ ShaderDataType::Float2, "a_TextureCoord"  },
        { ShaderDataType::Float,  "a_TextureIndex"  },
        { ShaderDataType::Float,  "a_TilingFactor"  },
	});

	s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
    s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

    // Index buffer.
    uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < s_Data.MaxIndices; i += QuadData::IndicesPerQuad)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;
        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += QuadData::VerticesPerQuad;
    }

	Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, 
        s_Data.MaxIndices);
	s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
    delete[] quadIndices;

    // Texture.
	s_Data.WhiteTexture = Texture2D::Create(1, 1);
	uint32_t whiteTextureData = 0xffffffff;
	s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    int32_t samplers[s_Data.MaxTextureSlots];
    for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
        samplers[i] = i;

    // Shader.
	s_Data.TextureShader = Shader::Create("../../assets/Shaders/Texture.glsl");
	s_Data.TextureShader->Bind();
	s_Data.TextureShader->SetIntArray("u_Textures", samplers,
        s_Data.MaxTextureSlots);

    // Add white texture to slot zero.
    s_Data.TextureSlots[0] = s_Data.WhiteTexture;

    // Vertex positions.
    s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f,  0.0f,  1.0f };
    s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f,  0.0f,  1.0f };
    s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f,  0.0f,  1.0f };
    s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f,  0.0f,  1.0f };

    // Texture coordinates.
    s_Data.QuadTextureCoords[0] = { 0.0f, 0.0f };
    s_Data.QuadTextureCoords[1] = { 1.0f, 0.0f };
    s_Data.QuadTextureCoords[2] = { 1.0f, 1.0f };
    s_Data.QuadTextureCoords[3] = { 0.0f, 1.0f };
}

void Renderer2D::Shutdown()
{
    s_Data.QuadIndexCount = 0;
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    s_Data.TextureSlotIndex = 1;

	delete[] s_Data.QuadVertexBufferBase;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
	s_Data.TextureShader->Bind();
	s_Data.TextureShader->SetMat4("u_ViewProjection",
		camera.GetViewProjectionMatrix());

    s_Data.QuadIndexCount = 0;
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

    s_Data.TextureSlotIndex = 1;
}

void Renderer2D::EndScene()
{
    uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr -
        (uint8_t*)s_Data.QuadVertexBufferBase;
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

    Flush();
}

void Renderer2D::Flush()
{
    // Bind textures.
    for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        s_Data.TextureSlots[i]->Bind(i);

    // Draw call.
    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

	s_Data.Stats.DrawCalls++;
}

void Renderer2D::FlushAndReset()
{
	EndScene();

	s_Data.QuadIndexCount = 0;
	s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	s_Data.TextureSlotIndex = 1;
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, 
	const glm::vec4& color)
{
	DrawQuad({ position.x, position.y, 0.0f }, size, color);
}
	
void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
	const glm::vec4& color)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
	const Ref<Texture2D>& texture, const float tilingFactor,
    const glm::vec4& tintColor)
{
	DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor,
        tintColor);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size,
	const Ref<Texture2D>& texture, const float tilingFactor,
    const glm::vec4& tintColor)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, 
    const glm::vec2& size, const float rotation, const glm::vec4& color)
{
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, 
    const glm::vec2& size, const float rotation, const glm::vec4& color)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, 
    const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, 
    const float tilingFactor, const glm::vec4& tintColor)
{
    DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture,
        tilingFactor, tintColor);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, 
    const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, 
    const float tilingFactor, const glm::vec4& tintColor)
{

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
        * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		FlushAndReset();

    constexpr const float textureIndex = 0.0f; // White texture.
    constexpr const float tilingFactor = 1.0f;

    for (uint32_t i = 0; i < QuadData::VerticesPerQuad; i++)
    {
        s_Data.QuadVertexBufferPtr->Position = transform * 
            s_Data.QuadVertexPositions[i];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TextureCoord = s_Data.QuadTextureCoords[i];
        s_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += QuadData::IndicesPerQuad;
	s_Data.Stats.QuadCount++;
}

void Renderer2D::DrawQuad(const glm::mat4& transform, 
	const Ref<Texture2D>& texture, const float tilingFactor, 
	const glm::vec4& tintColor)
{
	if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
		FlushAndReset();

    // Check if texture has already been submitted.
    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
    {
        if (*s_Data.TextureSlots[i].get() == *texture.get())
        {
            textureIndex = (float)i;
            break;
        }
    }

    // If not found, assign texture to new texture slot.
    if (textureIndex == 0.0f)
    {
        textureIndex = (float)s_Data.TextureSlotIndex;
        s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
        s_Data.TextureSlotIndex++;
    }

    for (uint32_t i = 0; i < QuadData::VerticesPerQuad; i++)
    {
        s_Data.QuadVertexBufferPtr->Position = transform * 
            s_Data.QuadVertexPositions[i];
        s_Data.QuadVertexBufferPtr->Color = tintColor;
        s_Data.QuadVertexBufferPtr->TextureCoord = s_Data.QuadTextureCoords[i];
        s_Data.QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;
    }

    s_Data.QuadIndexCount += QuadData::IndicesPerQuad;
	s_Data.Stats.QuadCount++;
}

void Renderer2D::ResetStats()
{
	memset(&s_Data.Stats, 0, sizeof(Statistics));
}

Renderer2D::Statistics Renderer2D::GetStats()
{
	return s_Data.Stats;
}

}

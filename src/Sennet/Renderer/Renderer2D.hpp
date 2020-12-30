#pragma once

#include "Sennet/Renderer/OrthographicCamera.hpp"
#include "Sennet/Renderer/Texture.hpp"

namespace Sennet
{

class Renderer2D
{
public:
    static void Init();
    static void Shutdown();
	
    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();
    static void Flush();

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size,
        const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size,
        const glm::vec4& color);
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size,
        const Ref<Texture2D>& texture, const float tilingFactor = 1.0f,
        const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size,
        const Ref<Texture2D>& texture, const float tilingFactor = 1.0f,
        const glm::vec4& tintColor = glm::vec4(1.0f));

    static void DrawRotatedQuad(const glm::vec2& position, 
        const glm::vec2& size, const float rotation, const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec3& position, 
        const glm::vec2& size, const float rotation, const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec2& position, 
        const glm::vec2& size, const float rotation, 
        const Ref<Texture2D>& texture, const float tilingFactor = 1.0f,
        const glm::vec4& tintColor = glm::vec4(1.0f));
    static void DrawRotatedQuad(const glm::vec3& position, 
        const glm::vec2& size, const float rotation,
        const Ref<Texture2D>& texture, const float tilingFactor = 1.0f,
        const glm::vec4& tintColor = glm::vec4(1.0f));

	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void DrawQuad(const glm::mat4& transform, 
		const Ref<Texture2D>& texture, const float tilingFactor = 1.0f,
		const glm::vec4& tintColor = glm::vec4(1.0f));

    struct QuadData
    {
		static const uint32_t VerticesPerQuad = 4;
        static const uint32_t IndicesPerQuad = 6;
    };

    struct Statistics
    {
		uint32_t DrawCalls = 0;
        uint32_t QuadCount = 0;

        uint32_t GetTotalVertexCount() 
        { 
            return QuadCount * QuadData::VerticesPerQuad; 
        }
        
        uint32_t GetTotalIndexCount() 
		{ 
			return QuadCount * QuadData::IndicesPerQuad; 
		}
    };

    static void ResetStats();
    static Statistics GetStats();

private:
	static void FlushAndReset();
};

}

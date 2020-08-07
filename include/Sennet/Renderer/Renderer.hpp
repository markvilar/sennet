#pragma once

#include <Sennet/Core/Base.hpp>

#include <Sennet/Renderer/OrthographicCamera.hpp>
#include <Sennet/Renderer/RendererAPI.hpp>
#include <Sennet/Renderer/Shader.hpp>

namespace Sennet
{

class Renderer
{
public:
	static void BeginScene(OrthographicCamera& camera);
	static void EndScene();

	static void Submit(const Ref<Shader>& shader,
		const Ref<VertexArray>& vertexArray);

	inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
	};

	static SceneData* m_SceneData;
};

}

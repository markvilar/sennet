#include <Sennet/pch.hpp>
#include <Sennet/Renderer/Renderer.hpp>

#include <Sennet/Renderer/RenderCommand.hpp>

namespace Sennet
{

Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

void Renderer::BeginScene(OrthographicCamera& camera)
{
	m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const Ref<Shader>& shader,
	const Ref<VertexArray>& vertexArray)
{
	shader->Bind();
	shader->UploadUniformMat4("u_ViewProjection", 
		m_SceneData->ViewProjectionMatrix);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

}

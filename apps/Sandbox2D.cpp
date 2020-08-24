#include "Sandbox2D.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

// Temporary.
#include <Sennet/Platform/OpenGL/OpenGLShader.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	// Square.
	m_SquareVA = Sennet::VertexArray::Create();

	float squareVertices[4 * 3] = 
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	
	Sennet::Ref<Sennet::VertexBuffer> squareVB(
		Sennet::VertexBuffer::Create(squareVertices,
		sizeof(squareVertices)));

	squareVB->SetLayout({
		{ Sennet::ShaderDataType::Float3, "a_Position" }
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

	Sennet::Ref<Sennet::IndexBuffer> squareIB(
		Sennet::IndexBuffer::Create(squareIndices,
		sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Sennet::Shader::Create(
		"../../assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Sennet::Timestep ts)
{
	// Update.
	m_CameraController.OnUpdate(ts);

	// Render.
	Sennet::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
	Sennet::RenderCommand::Clear();

	Sennet::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<Sennet::OpenGLShader>(
		m_FlatColorShader)->Bind();

	std::dynamic_pointer_cast<Sennet::OpenGLShader>(
		m_FlatColorShader)->UploadUniformFloat4("u_Color",
		m_SquareColor);

	Sennet::Renderer::Submit(m_FlatColorShader, m_SquareVA, 
		glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Sennet::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::SameLine();
	Sennet::ImGuiHelpMarker("Click and drag the square to adjust "
		"the respective color component.");
	ImGui::End();
}

void Sandbox2D::OnEvent(Sennet::Event& e)
{
	m_CameraController.OnEvent(e);
}

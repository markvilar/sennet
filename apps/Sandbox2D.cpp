#include "Sandbox2D.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#define PROFILE_SCOPE(name) Sennet::Timer timer##__LINE__(	\
		name, [&](ProfileResult profileResult)		\
	{							\
		m_ProfileResults.push_back(profileResult);	\
	});							

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Sennet::Texture2D::Create(
		"../../assets/textures/Checkerboard-600x600.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Sennet::Timestep ts)
{
	PROFILE_SCOPE("Sennet::OnUpdate");

	// Update camera.
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render.
	{
		PROFILE_SCOPE("Renderer Prep");
		Sennet::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Sennet::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Sennet::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Sennet::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, 
			{ 0.8f, 0.2f, 0.3f, 1.0f });
		Sennet::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, 
			m_SquareColor);
		Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, 
			{ 10.0f, 10.0f }, m_CheckerboardTexture);
		Sennet::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	/*
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar 
		| ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar 
			| ImGuiWindowFlags_NoCollapse 
			| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus 
			| ImGuiWindowFlags_NoNavFocus;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), 
			dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
				Sennet::Application::Get().Close();
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();

		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::SameLine();
		Sennet::ImGuiHelpMarker("Click and drag the square to adjust "
			"the respective color component.");

		uint32_t textureID = m_CheckerboardTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{256.0f, 256.0f});

		ImGui::End();
	}

	ImGui::End();
	*/

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3f ms   ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Sennet::Event& e)
{
	m_CameraController.OnEvent(e);
}

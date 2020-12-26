#include "Sandbox2D.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Sennet::Texture2D::Create(
		"../../assets/Textures/Checkerboard-600x600.png");
	m_SpriteSheet = Sennet::Texture2D::Create(
		"../../assets/Textures/RPGSpriteSheet.png");

	Sennet::Renderer2D::Init();
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Sennet::Timestep ts)
{
	SN_PROFILE_FUNCTION();

	// Update camera.
	{
		SN_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render.
	Sennet::Renderer2D::ResetStats();
	{
		SN_PROFILE_SCOPE("Renderer Prep");
		Sennet::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Sennet::RenderCommand::Clear();
	}

	{
        static float rotation = 0.0f;
        rotation += ts * 50.0f;

		SN_PROFILE_SCOPE("Renderer Draw");

		Sennet::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Sennet::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 0.8f, 0.8f }, 
            glm::radians(rotation), { 0.9f, 0.1f, 0.2f, 1.0f });
		Sennet::Renderer2D::DrawQuad({ 2.0f, -2.0f }, { 0.8f, 0.8f }, 
			{ 0.8f, 0.2f, 0.3f, 1.0f });
		Sennet::Renderer2D::DrawQuad({ 2.0f, 2.0f }, { 0.5f, 0.75f }, 
            m_QuadColor);
		Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 20.0f, 20.0f }, 
            m_CheckerboardTexture, 4.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
        Sennet::Renderer2D::DrawRotatedQuad({ -2.0f, -2.0f, 0.0f }, 
            { 1.0f, 1.0f }, glm::radians(45.0f), m_CheckerboardTexture, 1.0f, 
            glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));

		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, 
					(y + 5.0f) / 10.0f, 0.7f };
				Sennet::Renderer2D::DrawQuad({ x, y, -0.1f}, { 0.45f, 0.45f }, 
					color);
			}
		}

		Sennet::Renderer2D::DrawRotatedQuad({ -2.0f, 2.0f, 0.0f }, 
			{ 2.560f, 1.664f }, glm::radians(0.0f), m_SpriteSheet, 1.0f, 
            glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));

		Sennet::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	SN_PROFILE_FUNCTION();

	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool optionFullscreenPersistant = true;
		bool optionFullscreen = optionFullscreenPersistant;
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar 
			| ImGuiWindowFlags_NoDocking;
		if (optionFullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar 
				| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize 
				| ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus 
				| ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();
		
		if (optionFullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
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
		}

		ImGui::Begin("Settings");

		auto stats = Sennet::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_QuadColor));

		uint32_t textureID = m_CheckerboardTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();

	}
	else
	{
		ImGui::Begin("Settings");

		auto stats = Sennet::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_QuadColor));

		uint32_t textureID = m_CheckerboardTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}
}

void Sandbox2D::OnEvent(Sennet::Event& e)
{
	m_CameraController.OnEvent(e);
}

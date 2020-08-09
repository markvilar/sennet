#pragma once

#include <Sennet/Core/Base.hpp>
#include <Sennet/Core/Timestep.hpp>

#include <Sennet/Events/ApplicationEvent.hpp>
#include <Sennet/Events/MouseEvent.hpp>

#include <Sennet/Renderer/OrthographicCamera.hpp>

namespace Sennet
{

class OrthographicCameraController
{
public:
	OrthographicCameraController(float aspectRatio, bool rotation = false);

	void OnUpdate(Timestep ts);
	void OnEvent(Event& e);

	OrthographicCamera& GetCamera() { return m_Camera; }
	const OrthographicCamera& GetCamera() const { return m_Camera; }

private:
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResized(WindowResizeEvent& e);

private:
	float m_AspectRatio;
	float m_ZoomLevel = 1.0f;
	bool m_Rotation;

	OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraTranslationSpeed = 1.5f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 70.0f;
};

}
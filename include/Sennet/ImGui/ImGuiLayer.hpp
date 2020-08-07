#pragma once

#include <Sennet/Core/Layer.hpp>

#include <Sennet/Events/ApplicationEvent.hpp>
#include <Sennet/Events/KeyEvent.hpp>
#include <Sennet/Events/MouseEvent.hpp>

namespace Sennet
{

class ImGuiLayer : public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;

	void Begin();
	void End();

private:

private:
	float m_Time;

};

}

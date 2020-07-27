#include <sennet/snpch.hpp>
#include <sennet/imgui/imgui_layer.hpp>

#include <imgui.h>
#include <sennet/platform/opengl/imgui_opengl_renderer.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <sennet/core/application.hpp>

namespace sennet
{

imgui_layer::imgui_layer()
	: layer("imgui_layer"), m_time(0.0f)
{
}

void imgui_layer::on_attach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	// Temporary: Should eventually use sennet key codes.
	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui_ImplOpenGL3_Init("#version 410");
}

void imgui_layer::on_detach()
{
}

void imgui_layer::on_update()
{
	ImGuiIO& io= ImGui::GetIO();
	application& app = application::get();
	io.DisplaySize = ImVec2(app.get_window().get_width(),
		app.get_window().get_height());

	float time = (float)glfwGetTime();
	io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
	m_time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imgui_layer::on_event(event& e)
{
	event_dispatcher dispatcher(e);

	dispatcher.dispatch<mouse_button_pressed_event>(
		SN_BIND_EVENT_FN(imgui_layer::on_mouse_button_pressed_event));
	dispatcher.dispatch<mouse_button_released_event>(
		SN_BIND_EVENT_FN(imgui_layer::on_mouse_button_released_event));
	dispatcher.dispatch<mouse_moved_event>(
		SN_BIND_EVENT_FN(imgui_layer::on_mouse_moved_event));
	dispatcher.dispatch<mouse_scrolled_event>(
		SN_BIND_EVENT_FN(imgui_layer::on_mouse_scrolled_event));
	dispatcher.dispatch<key_pressed_event>(
		SN_BIND_EVENT_FN(imgui_layer::on_key_pressed_event));
	dispatcher.dispatch<key_released_event>(
		SN_BIND_EVENT_FN(imgui_layer::on_key_released_event));
	dispatcher.dispatch<key_typed_event>(
		SN_BIND_EVENT_FN(imgui_layer::on_key_typed_event));
	dispatcher.dispatch<window_resize_event>(
		SN_BIND_EVENT_FN(imgui_layer::on_window_resized_event));
}

bool imgui_layer::on_mouse_button_pressed_event(mouse_button_pressed_event& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[static_cast<int>(e.get_mouse_button())] = true;

	return false;
}

bool imgui_layer::on_mouse_button_released_event(mouse_button_released_event& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[static_cast<int>(e.get_mouse_button())] = false;

	return false;
}

bool imgui_layer::on_mouse_moved_event(mouse_moved_event& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(e.get_x(), e.get_y());

	return false;
}

bool imgui_layer::on_mouse_scrolled_event(mouse_scrolled_event& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += e.get_x_offset();
	io.MouseWheel += e.get_y_offset();

	return false;
}

bool imgui_layer::on_key_pressed_event(key_pressed_event& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[static_cast<int>(e.get_key_code())] = true;

	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
		io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] ||
		io.KeysDown[GLFW_KEY_RIGHT_SHIFT];;
	io.KeyAlt= io.KeysDown[GLFW_KEY_LEFT_ALT] ||
		io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper= io.KeysDown[GLFW_KEY_LEFT_SUPER] ||
		io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	return false;
}

bool imgui_layer::on_key_released_event(key_released_event& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[static_cast<int>(e.get_key_code())] = false;

	return false;
}

bool imgui_layer::on_key_typed_event(key_typed_event& e)
{
	ImGuiIO& io = ImGui::GetIO();
	auto keycode = static_cast<int>(e.get_key_code());
	if (keycode > 0 && keycode < 0x10000)
	{
		io.AddInputCharacter((unsigned short)keycode);
	}

	return false;
}

bool imgui_layer::on_window_resized_event(window_resize_event& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(e.get_width(), e.get_height());
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

	glViewport(0, 0, e.get_width(), e.get_height());

	return false;
}

}

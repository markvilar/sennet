#include <sennet/snpch.hpp>
#include <sennet/platform/opengl/opengl_context.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace sennet
{

opengl_context::opengl_context(GLFWwindow* window_handle)
	: m_window_handle(window_handle)
{
	SN_CORE_ASSERT(window_handle, "Window handle is null!")
}

void opengl_context::init()
{
	glfwMakeContextCurrent(m_window_handle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	SN_CORE_ASSERT(status, "Failed to initialize Glad!")

	SN_CORE_INFO("OpenGL Info:");
	SN_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
	SN_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
	SN_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));

#ifdef SN_ENABLE_ASSERTS
	int version_major;
	int version_minor;
	glGetIntegerv(GL_MAJOR_VERSION, &version_major);
	glGetIntegerv(GL_MINOR_VERSION, &version_minor);

	SN_CORE_ASSERT(version_major > 4 || 
		(version_major == 4 && version_minor >= 5),
		"Sennet requires at least OpenGL version 4.5!");
#endif
}

void opengl_context::swap_buffers()
{
	glfwSwapBuffers(m_window_handle);
}

}

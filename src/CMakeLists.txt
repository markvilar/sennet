set(SENNET_HDR
	"Sennet/Sennet.hpp"
	"Sennet/Core/Application.hpp"
	"Sennet/Core/Base.hpp"
	"Sennet/Core/Input.hpp"
	"Sennet/Core/KeyCodes.hpp"
	"Sennet/Core/Layer.hpp"
	"Sennet/Core/LayerStack.hpp"
	"Sennet/Core/Log.hpp"
	"Sennet/Core/MouseCodes.hpp"
	"Sennet/Core/Timestep.hpp"
	"Sennet/Core/Window.hpp"
	"Sennet/Debug/Instrumentor.hpp"
	"Sennet/Events/ApplicationEvent.hpp"
	"Sennet/Events/Event.hpp"
	"Sennet/Events/KeyEvent.hpp"
	"Sennet/Events/MouseEvent.hpp"
	"Sennet/ImGui/ImGuiLayer.hpp"
	"Sennet/ImGui/ImGuiUtilities.hpp"
	"Sennet/Network/Client.hpp"
	"Sennet/Network/Connection.hpp"
	"Sennet/Network/Message.hpp"
	"Sennet/Network/Server.hpp"
	"Sennet/Network/TSQueue.hpp"
	"Sennet/Renderer/Buffer.hpp"
	"Sennet/Renderer/Framebuffer.hpp"
	"Sennet/Renderer/GraphicsContext.hpp"	
	"Sennet/Renderer/OrthographicCamera.hpp"	
	"Sennet/Renderer/OrthographicCameraController.hpp"	
	"Sennet/Renderer/RenderCommand.hpp"
	"Sennet/Renderer/Renderer.hpp"
	"Sennet/Renderer/Renderer2D.hpp"
	"Sennet/Renderer/RendererAPI.hpp"
	"Sennet/Renderer/Shader.hpp"
	"Sennet/Renderer/Texture.hpp"
	"Sennet/Renderer/VertexArray.hpp"
	"Sennet/Synchronization/Synchronizer.hpp"
	"Sennet/Synchronization/Timestamp.hpp")

set(SENNET_SRC
	"Sennet/Core/Application.cpp"
	"Sennet/Core/Layer.cpp"
	"Sennet/Core/LayerStack.cpp"
	"Sennet/Core/Log.cpp"
	"Sennet/Core/Window.cpp"
	"Sennet/ImGui/ImGuiBuild.cpp"
	"Sennet/ImGui/ImGuiLayer.cpp"
	"Sennet/ImGui/ImGuiUtilities.cpp"
	"Sennet/Renderer/Buffer.cpp"
	"Sennet/Renderer/Framebuffer.cpp"
	"Sennet/Renderer/GraphicsContext.cpp"
	"Sennet/Renderer/OrthographicCamera.cpp"
	"Sennet/Renderer/OrthographicCameraController.cpp"
	"Sennet/Renderer/RenderCommand.cpp"
	"Sennet/Renderer/Renderer.cpp"
	"Sennet/Renderer/Renderer2D.cpp"
	"Sennet/Renderer/RendererAPI.cpp"
	"Sennet/Renderer/Shader.cpp"
	"Sennet/Renderer/Texture.cpp"
	"Sennet/Renderer/VertexArray.cpp")

set(PLATFORM_HDR
	"Platform/OpenGL/OpenGLBuffer.hpp"
	"Platform/OpenGL/OpenGLFramebuffer.hpp"
	"Platform/OpenGL/OpenGLContext.hpp"
	"Platform/OpenGL/OpenGLRendererAPI.hpp"
	"Platform/OpenGL/OpenGLShader.hpp"
	"Platform/OpenGL/OpenGLTexture.hpp"
	"Platform/OpenGL/OpenGLVertexArray.hpp"
	"Platform/Windows/WindowsWindow.hpp"
	"Platform/Linux/LinuxWindow.hpp")

set(PLATFORM_SRC
	"Platform/OpenGL/OpenGLBuffer.cpp"
	"Platform/OpenGL/OpenGLFramebuffer.cpp"
	"Platform/OpenGL/OpenGLContext.cpp"
	"Platform/OpenGL/OpenGLRendererAPI.cpp"
	"Platform/OpenGL/OpenGLShader.cpp"
	"Platform/OpenGL/OpenGLTexture.cpp"
	"Platform/OpenGL/OpenGLVertexArray.cpp"
	"Platform/Windows/WindowsInput.cpp"
	"Platform/Windows/WindowsWindow.cpp"
	"Platform/Linux/LinuxInput.cpp"
	"Platform/Linux/LinuxWindow.cpp")

# Sennet - Static library.
add_library(Sennet STATIC
	${SENNET_HDR}
	${SENNET_SRC}
	${PLATFORM_HDR}
	${PLATFORM_SRC})

# Sennet - Precompiled header.
target_precompile_headers(Sennet 
	PRIVATE
	"Sennet/Pch.hpp")

# Sennet - Including.
target_include_directories(Sennet 
	PUBLIC 
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/extern/asio/asio/include"
	"${PROJECT_SOURCE_DIR}/extern/glad/include"
	"${PROJECT_SOURCE_DIR}/extern/glfw/include"
	"${PROJECT_SOURCE_DIR}/extern/glm"
	"${PROJECT_SOURCE_DIR}/extern/imgui"
	"${PROJECT_SOURCE_DIR}/extern/spdlog/include"
	"${PROJECT_SOURCE_DIR}/extern/stb") 

# Sennet - Linking.
target_link_libraries(Sennet 
	PRIVATE 
	glad
	glfw
	imgui
	spdlog
	stb)

# Sennet - Definitions.
target_compile_definitions(Sennet
	PRIVATE
	GLFW_INCLUDE_NONE)

# Sennet - Compilation features.
target_compile_features(Sennet 
	PUBLIC 
	cxx_std_17)

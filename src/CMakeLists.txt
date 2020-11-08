# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/Sennet/Sennet.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/Application.hpp"	
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/Base.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/Input.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/KeyCodes.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/Layer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/LayerStack.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/Log.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/MouseCodes.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/Timestep.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Core/Window.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Debug/Timer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Events/ApplicationEvent.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Events/Event.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Events/KeyEvent.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Events/MouseEvent.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ImGui/ImGuiLayer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/ImGui/ImGuiUtilities.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Network/Client.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Network/Connection.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Network/Message.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Network/Server.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Network/TSQueue.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Platform/OpenGL/OpenGLBuffer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Platform/OpenGL/OpenGLContext.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Platform/OpenGL/OpenGLRendererAPI.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Platform/OpenGL/OpenGLShader.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Platform/OpenGL/OpenGLTexture.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Platform/OpenGL/OpenGLVertexArray.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Platform/Windows/WindowsWindow.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Platform/Linux/LinuxWindow.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/Buffer.hpp"	
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/GraphicsContext.hpp"	
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/OrthographicCamera.hpp"	
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/OrthographicCameraController.hpp"	
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/RenderCommand.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/Renderer.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/Renderer2D.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/RendererAPI.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/Shader.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/Texture.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Renderer/VertexArray.hpp"
	"${PROJECT_SOURCE_DIR}/include/Sennet/Primitives/Image.hpp")

# Add sennet as a static library
add_library(Sennet STATIC
	Core/Application.cpp
	Core/Layer.cpp
	Core/LayerStack.cpp
	Core/Log.cpp
	Core/Window.cpp
	ImGui/ImGuiBuild.cpp
	ImGui/ImGuiLayer.cpp
	ImGui/ImGuiUtilities.cpp
	Platform/OpenGL/OpenGLBuffer.cpp
	Platform/OpenGL/OpenGLContext.cpp
	Platform/OpenGL/OpenGLRendererAPI.cpp
	Platform/OpenGL/OpenGLShader.cpp
	Platform/OpenGL/OpenGLTexture.cpp
	Platform/OpenGL/OpenGLVertexArray.cpp
	Platform/Windows/WindowsInput.cpp
	Platform/Windows/WindowsWindow.cpp
	Platform/Linux/LinuxInput.cpp
	Platform/Linux/LinuxWindow.cpp
	Renderer/Buffer.cpp
	Renderer/GraphicsContext.cpp
	Renderer/OrthographicCamera.cpp
	Renderer/OrthographicCameraController.cpp
	Renderer/RenderCommand.cpp
	Renderer/Renderer.cpp
	Renderer/Renderer2D.cpp
	Renderer/RendererAPI.cpp
	Renderer/Shader.cpp
	Renderer/Texture.cpp
	Renderer/VertexArray.cpp
	Primitives/Image.cpp
	${HEADER_LIST})

# Precompiled headers
target_precompile_headers(Sennet 
	PRIVATE
	"${PROJECT_SOURCE_DIR}/include/Sennet/pch.hpp")

# Include headers and source code from other libraries in sennet. This way we
# won't have to link all of sennet dependencies into targets that use
# sennet, but just sennet library itself.
target_include_directories(Sennet 
	PUBLIC 
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/extern/asio/asio/include"
	"${PROJECT_SOURCE_DIR}/extern/glad/include"
	"${PROJECT_SOURCE_DIR}/extern/glfw/include"
	"${PROJECT_SOURCE_DIR}/extern/glm"
	"${PROJECT_SOURCE_DIR}/extern/imgui"
	"${PROJECT_SOURCE_DIR}/extern/serializer/include"
	"${PROJECT_SOURCE_DIR}/extern/spdlog/include"
	"${PROJECT_SOURCE_DIR}/extern/stb"
	) 
		
target_link_libraries(Sennet 
	PRIVATE 
	glad
	glfw
	imgui
	stb
	spdlog
	)

# Define macros.
target_compile_definitions(Sennet
	PRIVATE
	)

# All users of this will need at least C++17
target_compile_features(Sennet 
	PUBLIC 
	cxx_std_17
	)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES
	${HEADER_LIST})

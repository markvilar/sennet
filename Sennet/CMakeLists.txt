set(SENNET_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Sennet/include")
set(SENNET_SOURCE_DIR "${PROJECT_SOURCE_DIR}/Sennet/src")

set(SENNET_HDR
	"${SENNET_INCLUDE_DIR}/Sennet/Sennet.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Containers/Image.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/Application.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/Base.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/Input.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/KeyCodes.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/Layer.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/LayerStack.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/Log.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/MouseCodes.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/Timestep.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Core/Window.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Debug/Instrumentor.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Events/ApplicationEvent.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Events/Event.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Events/KeyEvent.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Events/MouseEvent.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/ImGui/ImGuiLayer.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/ImGui/ImGuiUtilities.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Network/Client.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Network/Connection.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Network/Message.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Network/Server.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Network/TSQueue.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/Buffer.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/Framebuffer.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/GraphicsContext.hpp"	
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/OrthographicCamera.hpp"	
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/OrthographicCameraController.hpp"	
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/RenderCommand.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/Renderer.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/Renderer2D.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/RendererAPI.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/Shader.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/Texture.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Renderer/VertexArray.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Synchronization/Synchronizer.hpp"
	"${SENNET_INCLUDE_DIR}/Sennet/Synchronization/Timestamp.hpp")

set(SENNET_SRC
	"${SENNET_SOURCE_DIR}/Sennet/Core/Application.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Core/Layer.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Core/LayerStack.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Core/Log.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Core/Window.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/ImGui/ImGuiBuild.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/ImGui/ImGuiLayer.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/ImGui/ImGuiUtilities.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/Buffer.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/Framebuffer.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/GraphicsContext.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/OrthographicCamera.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/OrthographicCameraController.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/RenderCommand.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/Renderer.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/Renderer2D.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/RendererAPI.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/Shader.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/Texture.cpp"
	"${SENNET_SOURCE_DIR}/Sennet/Renderer/VertexArray.cpp")

set(SENNET_PLATFORM_HDR
	"${SENNET_INCLUDE_DIR}/Platform/OpenGL/OpenGLBuffer.hpp"
	"${SENNET_INCLUDE_DIR}/Platform/OpenGL/OpenGLFramebuffer.hpp"
	"${SENNET_INCLUDE_DIR}/Platform/OpenGL/OpenGLContext.hpp"
	"${SENNET_INCLUDE_DIR}/Platform/OpenGL/OpenGLRendererAPI.hpp"
	"${SENNET_INCLUDE_DIR}/Platform/OpenGL/OpenGLShader.hpp"
	"${SENNET_INCLUDE_DIR}/Platform/OpenGL/OpenGLTexture.hpp"
	"${SENNET_INCLUDE_DIR}/Platform/OpenGL/OpenGLVertexArray.hpp"
	"${SENNET_INCLUDE_DIR}/Platform/Windows/WindowsWindow.hpp"
	"${SENNET_INCLUDE_DIR}/Platform/Linux/LinuxWindow.hpp")

set(SENNET_PLATFORM_SRC
	"${SENNET_SOURCE_DIR}/Platform/OpenGL/OpenGLBuffer.cpp"
	"${SENNET_SOURCE_DIR}/Platform/OpenGL/OpenGLFramebuffer.cpp"
	"${SENNET_SOURCE_DIR}/Platform/OpenGL/OpenGLContext.cpp"
	"${SENNET_SOURCE_DIR}/Platform/OpenGL/OpenGLRendererAPI.cpp"
	"${SENNET_SOURCE_DIR}/Platform/OpenGL/OpenGLShader.cpp"
	"${SENNET_SOURCE_DIR}/Platform/OpenGL/OpenGLTexture.cpp"
	"${SENNET_SOURCE_DIR}/Platform/OpenGL/OpenGLVertexArray.cpp"
	"${SENNET_SOURCE_DIR}/Platform/Windows/WindowsInput.cpp"
	"${SENNET_SOURCE_DIR}/Platform/Windows/WindowsWindow.cpp"
	"${SENNET_SOURCE_DIR}/Platform/Linux/LinuxInput.cpp"
	"${SENNET_SOURCE_DIR}/Platform/Linux/LinuxWindow.cpp")

add_library(Sennet STATIC 
	${SENNET_HDR}
	${SENNET_SRC}
	${SENNET_PLATFORM_HDR}
	${SENNET_PLATFORM_SRC})

target_precompile_headers(Sennet PRIVATE 
	"${SENNET_INCLUDE_DIR}/Sennet/Pch.hpp")

# External libraries.
add_subdirectory(vendor)

# Executables.
add_subdirectory(apps)

target_include_directories(Sennet PUBLIC 
	"${SENNET_INCLUDE_DIR}"
	"vendor/asio/asio/include"
	"vendor/glad/include"
	"vendor/glfw/include"
	"vendor/glm"
	"vendor/imgui"
	"vendor/spdlog/include"
	"vendor/stb") 

target_link_libraries(Sennet PRIVATE glad glfw imgui spdlog)

# Build type flags.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSN_DEBUG")
set(CMAKE_CXX_FLAGS_REALESE "${CMAKE_CXX_FLAGS_REALESE} -DSN_REALESE")

# Build platform flags.
if(UNIX)
	string(CONCAT CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} " "-DSN_PLATFORM_LINUX "
		"-DGLFW_INCLUDE_NONE ")
elseif(WIN32)
	string(CONCAT CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} " "-DSN_PLATFORM_WINDOWS "
		"-DGLFW_INCLUDE_NONE ")
endif()

message("\nCMake System: ${CMAKE_SYSTEM}")
message("CMake C++ compiler: ${CMAKE_CXX_COMPILER}\n")

message(STATUS "Sennet build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Sennet C++ flags: ${CMAKE_CXX_FLAGS}")

target_compile_definitions(Sennet PRIVATE)
target_compile_features(Sennet PUBLIC cxx_std_17)

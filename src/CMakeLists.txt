# Temporaries
set(TEMP_HEADERS
	"${PROJECT_SOURCE_DIR}/include/sennet/platform/opengl/imgui_opengl_renderer.h"
	)

set(TEMP_SRC
	platform/opengl/imgui_opengl_renderer.cpp
	)

# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/sennet/sennet.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/application.hpp"	
	"${PROJECT_SOURCE_DIR}/include/sennet/core/base.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/input.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/key_codes.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/layer.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/layer_stack.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/log.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/mouse_codes.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/source_handle.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/window.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/events/application_event.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/events/event.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/events/key_event.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/events/mouse_event.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/imgui/imgui_layer.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/messages/hello_world_message.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/messages/message.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/messages/message_encoder.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/network/connection.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/network/connection_manager.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/platform/opengl/opengl_context.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/platform/windows/windows_window.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/platform/linux/linux_window.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/renderer/graphics_context.hpp"	
	"${PROJECT_SOURCE_DIR}/include/sennet/types/basic_types.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/types/zed.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/zed/conversion.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/zed/io.hpp"	
	"${PROJECT_SOURCE_DIR}/include/sennet/zed/recorder.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/zed/serialization.hpp"
	)

# Add sennet as a static library
add_library(sennet STATIC
	core/application.cpp
	core/layer.cpp
	core/layer_stack.cpp
	core/log.cpp
	core/window.cpp
	imgui/imgui_layer.cpp
	messages/hello_world_message.cpp
	messages/message_encoder.cpp
	network/connection.cpp
	network/connection_manager.cpp 
	platform/opengl/opengl_context.cpp
	platform/windows/windows_input.cpp
	platform/windows/windows_window.cpp
	platform/linux/linux_input.cpp
	platform/linux/linux_window.cpp
	renderer/graphics_context.cpp
	types/basic_types.cpp
	types/zed.cpp
	zed/conversion.cpp
	zed/io.cpp 	
	zed/recorder.cpp
	${HEADER_LIST}
	${TEMP_HEADERS}
	${TEMP_SRC}
	)

# Precompiled headers
target_precompile_headers(sennet
	PRIVATE
	"${PROJECT_SOURCE_DIR}/include/sennet/snpch.hpp"
	)

# Include headers and source code from other libraries in sennet. This way we
# won't have to link all of sennet dependencies into targets that use
# sennet, but just sennet library itself.
target_include_directories(sennet 
	PUBLIC 
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/extern/glad/include"
	"${PROJECT_SOURCE_DIR}/extern/glfw/include"
	"${PROJECT_SOURCE_DIR}/extern/glm"
	"${PROJECT_SOURCE_DIR}/extern/imgui"
	"${PROJECT_SOURCE_DIR}/extern/libnop/include"
	"${PROJECT_SOURCE_DIR}/extern/spdlog/include"
	${Boost_INCLUDE_DIRS} 
	${CUDA_INCLUDE_DIRS} 
	${ZED_INCLUDE_DIRS}
	) 
		
# This depends on ZED and Boost features that needs to be linked to the library.
target_link_libraries(sennet 
	PRIVATE 
	Boost::serialization
	Boost::thread
	glad
	glfw
	imgui
	${ZED_LIBS}
	) 

# Define macros.
target_compile_definitions(sennet
	PRIVATE
	)

# All users of this will need at least C++17
target_compile_features(sennet 
	PUBLIC 
	cxx_std_17
	)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES
	${HEADER_LIST})

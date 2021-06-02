set(SENNET_EDITOR_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Editor/include")
set(SENNET_EDITOR_SOURCE_DIR "${PROJECT_SOURCE_DIR}/Editor/src")

set(SENNET_EDITOR_HDR "${SENNET_EDITOR_INCLUDE_DIR}/Editor/EditorLayer.hpp")
set(SENNET_EDITOR_SRC "${SENNET_EDITOR_SOURCE_DIR}/Editor/EditorLayer.cpp")
	
add_library(Sennet-Editor STATIC 
	${SENNET_EDITOR_HDR}
	${SENNET_EDITOR_SRC})

target_include_directories(Sennet-Editor PUBLIC
	"${PROJECT_SOURCE_DIR}/Editor/include"
	"${PROJECT_SOURCE_DIR}/extern/glm"
	"${PROJECT_SOURCE_DIR}/extern/imgui"
	"${PROJECT_SOURCE_DIR}/extern/spdlog/include")

add_subdirectory(vendor)
add_subdirectory(apps)

target_link_libraries(Sennet-Editor PRIVATE Sennet)
target_compile_definitions(Sennet-Editor PRIVATE)
target_compile_features(Sennet-Editor PUBLIC cxx_std_17)

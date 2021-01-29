# Git submodule - glad
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glad/CMakeLists.txt")
    	message(FATAL_ERROR "Sennet submodule glad was not downloaded! "
		"GIT_SUBMODULE was turned off or failed. Please update submodules and "
		"try again.")
endif()

# Git submodule - glfw
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glfw/CMakeLists.txt")
    	message(FATAL_ERROR "Sennet submodule glfw was not downloaded! "
		"GIT_SUBMODULE was turned off or failed. Please update submodules and "
		"try again.")
endif()

# Git submodule - glm
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glm/CMakeLists.txt")
    	message(FATAL_ERROR "Sennet submodule glm was not downloaded! "
		"GIT_SUBMODULE was turned off or failed. Please update submodules and "
		"try again.")
endif()

# Git submodule - imgui
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui/CMakeLists.txt")
    	message(FATAL_ERROR "Sennet submodule imgui was not downloaded! "
		"GIT_SUBMODULE was turned off or failed. Please update submodules and "
		"try again.")
endif()

# Git submodule - spdlog
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/spdlog/CMakeLists.txt")
    	message(FATAL_ERROR "Sennet submodule spdlog was not downloaded! "
		"GIT_SUBMODULE was turned off or failed. Please update submodules and "
		"try again.")
endif()

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(imgui)
add_subdirectory(spdlog)
add_subdirectory(stb)

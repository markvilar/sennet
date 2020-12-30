# Project
cmake_minimum_required(VERSION 3.16)
project(Sennet VERSION 1.0 LANGUAGES CXX C)

# Build configurations
add_compile_definitions(SN_DEBUG)
add_compile_definitions(SN_PLATFORM_LINUX)

# If main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	# Let's ensure -std=c++xx instead of -std=g++xx
	set(CMAKE_CXX_EXTENSIONS OFF)
	# Support folders in IDEs
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	# Enable testing
	include(CTest)
endif()

# Find packages
find_package(Git QUIET REQUIRED)

# Update Git submodules
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
	# Update submodules as needed
    	option(GIT_SUBMODULE "Check submodules during build" ON)
    	if(GIT_SUBMODULE)
        	message(STATUS "Submodule update")
        	execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
				--recursive WORKING_DIRECTORY 
				${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE
                        	GIT_SUBMOD_RESULT)
        	if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            		message(FATAL_ERROR CONCAT "git submodule update --init "
				"failed with ${GIT_SUBMOD_RESULT}, please "
				"checkout submodules.")
        	endif()
    	endif()
endif()

# Git submodule - entt
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/entt/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()


# Git submodule - glad
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/glad/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()

# Git submodule - glfw
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/glfw/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()

# Git submodule - glm
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/glm/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()

# Git submodule - imgui
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/imgui/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()

# Git submodule - spdlog
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/spdlog/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()

# Library code
add_subdirectory(src)

# Executable code - compile if main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	add_subdirectory(apps)
endif()

# External libraries
add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/imgui)
add_subdirectory(extern/spdlog)
add_subdirectory(extern/stb)

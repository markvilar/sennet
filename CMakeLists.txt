# Project
cmake_minimum_required(VERSION 3.16)
project(Sennet VERSION 0.1 LANGUAGES CXX C)

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
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update 
			--init --recursive WORKING_DIRECTORY 
			${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR CONCAT "git submodule update --init "
			"failed with ${GIT_SUBMOD_RESULT}, please checkout "
			"submodules.")
        endif()
    endif()
endif()

# Sennet library
add_subdirectory(Sennet)

# Editor library
add_subdirectory(Editor)

# Executable code - compile if main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	add_subdirectory(Applications)
endif()
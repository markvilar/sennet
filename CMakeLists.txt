cmake_minimum_required(VERSION 3.16)

# -----------------------------------------------------------------------------
# ---- Sennet project ---------------------------------------------------------
# -----------------------------------------------------------------------------

project(Sennet VERSION 0.1 LANGUAGES CXX)

# -----------------------------------------------------------------------------
# ---- Main -------------------------------------------------------------------
# -----------------------------------------------------------------------------

if(NOT DEFINED SENNET_MAIN_PROJECT)
	if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
		set(SENNET_MAIN_PROJECT ON)
	else()
		set(SENNET_MAIN_PROJECT OFF)
	endif()
endif()

# -----------------------------------------------------------------------------
# ---- Build type -------------------------------------------------------------
# -----------------------------------------------------------------------------

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Realese" CACHE STRING "Choose Realese or Debug." 
		FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSN_DEBUG")
set(CMAKE_CXX_FLAGS_REALESE "${CMAKE_CXX_FLAGS_REALESE} -DSN_REALESE")

# -----------------------------------------------------------------------------
# ---- Compiler configuration -------------------------------------------------
# -----------------------------------------------------------------------------

if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(SENNET_MAIN_PROJECT)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# -----------------------------------------------------------------------------
# ---- Build options ----------------------------------------------------------
# -----------------------------------------------------------------------------

option(SENNET_BUILD_SHARED "Build shared library." OFF)
option(SENNET_BUILD_EXAMPLE "Build library example." ON)
option(SENNET_BUILD_EDITOR "Build editor." ${SENNET_MAIN_PROJECT})
option(SENNET_BUILD_WARNINGS "Enable compiler warnings." OFF)

# -----------------------------------------------------------------------------
# ---- Git --------------------------------------------------------------------
# -----------------------------------------------------------------------------

find_package(Git QUIET REQUIRED)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init 
			--recursive WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
			RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR CONCAT "git submodule update --init failed "
				"with ${GIT_SUBMOD_RESULT}, please checkout submodules.")
        endif()
    endif()
endif()

# -----------------------------------------------------------------------------
# ---- Build platform ---------------------------------------------------------
# -----------------------------------------------------------------------------

# TODO: Cross-compilation support.
if(UNIX)
	string(JOIN " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" "-DSN_PLATFORM_LINUX"
		"-DGLFW_INCLUDE_NONE")
elseif(WIN32)
	string(JOIN " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" "-DSN_PLATFORM_WINDOWS"
		"-DGLFW_INCLUDE_NONE")
endif()

# -----------------------------------------------------------------------------
# ---- Print ------------------------------------------------------------------
# -----------------------------------------------------------------------------

message(STATUS "System: ${CMAKE_SYSTEM}")
message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "System version: ${CMAKE_SYSTEM_VERSION}")
message(STATUS "System processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "System host name: ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")

message(STATUS "Sennet build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Sennet C++ flags: ${CMAKE_CXX_FLAGS}")

# -----------------------------------------------------------------------------
# ---- Source -----------------------------------------------------------------
# -----------------------------------------------------------------------------


add_subdirectory(Sennet)

if(SENNET_BUILD_EDITOR)
	add_subdirectory(Editor)
endif()

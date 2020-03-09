# Project
cmake_minimum_required(VERSION 3.13)
project(ZEDutils VERSION 1.0 LANGUAGES CXX C)


# If main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	# Let's ensure -std=c++xx instead of -std=g++xx
	set(CMAKE_CXX_EXTENSIONS OFF)
	# Support folders in IDEs
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	# Enable testing
	include(CTest)
endif()


if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 OLD)
	cmake_policy(SET CMP0015 OLD)
endif(COMMAND cmake_policy)


# Find packages
find_package(Git QUIET)
find_package(Threads)
find_package(Boost COMPONENTS chrono system thread REQUIRED)
message(STATUS "Found Boost ${Boost_VERSION_STRING} at ${BOOST_ROOT}")
find_package(ZED 3 REQUIRED)
find_package(CUDA ${ZED_CUDA_VERSION} EXACT REQUIRED)
message(STATUS "Found CUDA ${CUDA_VERSION_STRING} at ${CUDA_TOOLKIT_ROOT_DIR}")


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


# Git submodule - Boostnet
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/boostnet/CMakeLists.txt")
    	message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE "
		"was turned off or failed. Please update submodules and try "
		"again.")
endif()


# Package options
option(Boost_USE_STATIC_LIBS "Link with the Boost static libraries" ON)
option(LINK_SHARED_ZED "Link with the ZED SDK shared executable" ON)

if(NOT LINK_SHARED_ZED AND MSVC)
    message(FATAL_ERROR "LINK_SHARED_ZED OFF : ZED SDK static libraries not available on Windows")
endif()

# ZED libraries - static or dynamic linking
if(LINK_SHARED_ZED)
    	SET(ZED_LIBS ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} 
		${CUDA_CUDART_LIBRARY} ${CUDA_NPP_LIBRARIES_ZED})
else()
    	SET(ZED_LIBS ${ZED_STATIC_LIBRARIES} ${CUDA_CUDA_LIBRARY} 
		${CUDA_LIBRARY})
endif()


# Library code
add_subdirectory(src)


# Executable code - compile if main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	add_subdirectory(apps)
endif()


# External libraries
add_subdirectory(extern/boostnet)


# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND 
	BUILD_TESTING)
	add_subdirectory(tests)
endif()

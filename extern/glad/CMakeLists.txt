# Project
cmake_minimum_required(VERSION 3.13)
project(glad VERSION 1.0 LANGUAGES CXX C)


# If main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	# Let's ensure -std=c++xx instead of -std=g++xx
	set(CMAKE_CXX_EXTENSIONS OFF)
	# Support folders in IDEs
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	# Enable testing
	include(CTest)
endif()

# Library code
add_subdirectory(src)

# Executable code - compile if main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	add_subdirectory(apps)
endif()

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND 
	BUILD_TESTING)
	add_subdirectory(tests)
endif()

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

# Editor
add_executable(Editor Editor.cpp)
target_compile_definitions(Editor PRIVATE)
target_compile_features(Editor PRIVATE cxx_std_17)
target_link_libraries(Editor PRIVATE Sennet-Editor Sennet)

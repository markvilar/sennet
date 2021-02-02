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

# Client
add_executable(Client Client.cpp)
target_compile_features(Client PRIVATE cxx_std_17)
target_compile_definitions(Client PRIVATE)
target_link_libraries(Client PRIVATE Sennet)

# Server
add_executable(Server Server.cpp)
target_compile_features(Server PRIVATE cxx_std_17)
target_compile_definitions(Server PRIVATE)
target_link_libraries(Server PRIVATE Sennet)

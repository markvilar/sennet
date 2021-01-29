# Build type.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSN_DEBUG")
set(CMAKE_CXX_FLAGS_REALESE "${CMAKE_CXX_FLAGS_REALESE} -DSN_REALESE")

# Client
add_executable(Client Client.cpp)
target_compile_features(Client PRIVATE cxx_std_17)
target_compile_definitions(Client PRIVATE 
	"-DSN_PLATFORM_LINUX" 
	"-DGLFW_INCLUDE_NONE")
target_link_libraries(Client PRIVATE Sennet)

# Server
add_executable(Server Server.cpp)
target_compile_features(Server PRIVATE cxx_std_17)
target_compile_definitions(Server PRIVATE 
	"-DSN_PLATFORM_LINUX"
	"-DGLFW_INCLUDE_NONE")
target_link_libraries(Server PRIVATE Sennet)

# Client
add_executable(Client Client.cpp)
target_compile_features(Client PRIVATE cxx_std_17)
target_link_libraries(Client PRIVATE Sennet)

# Sandbox
add_executable(Sandbox Sandbox.cpp)
target_compile_features(Sandbox PRIVATE cxx_std_17)
target_link_libraries(Sandbox PRIVATE Sennet Sandbox2D)

# Server
add_executable(Server Server.cpp)
target_compile_features(Server PRIVATE cxx_std_17)
target_link_libraries(Server PRIVATE Sennet)

# Sandbox library
add_library(Sandbox2D STATIC Sandbox2D.hpp Sandbox2D.cpp)
target_include_directories(Sandbox2D PUBLIC)
target_link_libraries(Sandbox2D PRIVATE Sennet)
target_compile_features(Sandbox2D PUBLIC cxx_std_17)

# UHINode
add_executable(UHINode UHINode.cpp)
target_compile_features(UHINode PRIVATE cxx_std_17)
target_link_libraries(UHINode PRIVATE Sennet)

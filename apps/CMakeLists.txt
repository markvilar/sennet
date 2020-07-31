# Client
add_executable(client client.cpp)
target_compile_features(client PRIVATE cxx_std_17)
target_link_libraries(client PRIVATE sennet)

# Sandbox
add_executable(sandbox sandbox.cpp)
target_compile_features(sandbox PRIVATE cxx_std_17)
target_link_libraries(sandbox PRIVATE sennet)

# Serialization
add_executable(serialization serialization.cpp)
target_compile_features(serialization PRIVATE cxx_std_17)
target_link_libraries(serialization PRIVATE sennet)

# Server
add_executable(server server.cpp)
target_compile_features(server PRIVATE cxx_std_17)
target_link_libraries(server PRIVATE sennet)

# Simple sandbox
add_executable(simple simple.cpp)
target_compile_features(simple PRIVATE cxx_std_17)
target_link_libraries(simple PRIVATE)

# Test - ZED
add_executable(test_zed test_zed.cpp)
target_compile_features(test_zed PRIVATE cxx_std_17)
target_link_libraries(test_zed PRIVATE sennet Boost::program_options)

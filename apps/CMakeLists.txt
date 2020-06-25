# Node - User
add_executable(node_user node_user.cpp)
target_compile_features(node_user PRIVATE cxx_std_17)
target_link_libraries(node_user PRIVATE zedutils) 

# Node - ZED
add_executable(node_zed node_zed.cpp)
target_compile_features(node_zed PRIVATE cxx_std_17)
target_link_libraries(node_zed PRIVATE zedutils)

# Sandbox
add_executable(sandbox sandbox.cpp)
target_compile_features(sandbox PRIVATE cxx_std_17)
target_link_libraries(sandbox PRIVATE 
	zedutils
	glad
	)

# Test - Hello world
add_executable(test_hello_world test_hello_world.cpp)
target_compile_features(test_hello_world PRIVATE cxx_std_17)
target_link_libraries(test_hello_world PRIVATE 
	zedutils
	Boost::program_options
	)

# Test - Serialization
add_executable(test_serialization test_serialization.cpp)
target_compile_features(test_serialization PRIVATE cxx_std_17)
target_link_libraries(test_serialization PRIVATE zedutils)

# Test - User
add_executable(test_user test_user.cpp)
target_compile_features(test_user PRIVATE cxx_std_17)
target_link_libraries(test_user PRIVATE zedutils)

# Test - ZED
add_executable(test_zed test_zed.cpp)
target_compile_features(test_zed PRIVATE cxx_std_17)
target_link_libraries(test_zed PRIVATE 
	zedutils
	Boost::program_options
	)

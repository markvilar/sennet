# Sandbox
add_executable(sandbox sandbox.cpp)
target_compile_features(sandbox PRIVATE cxx_std_17)
target_link_libraries(sandbox PRIVATE 
	sennet
	glad
	)

# Test - Hello world
add_executable(test_hello_world test_hello_world.cpp)
target_compile_features(test_hello_world PRIVATE cxx_std_17)
target_link_libraries(test_hello_world PRIVATE 
	sennet
	Boost::program_options
	)

# Test - Serialization
add_executable(test_serialization test_serialization.cpp)
target_compile_features(test_serialization PRIVATE cxx_std_17)
target_link_libraries(test_serialization PRIVATE sennet)

# Test - ZED
add_executable(test_zed test_zed.cpp)
target_compile_features(test_zed PRIVATE cxx_std_17)
target_link_libraries(test_zed PRIVATE 
	sennet
	Boost::program_options
	)

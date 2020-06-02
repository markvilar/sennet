# Node - UHI
add_executable(node_uhi node_uhi.cpp)
target_compile_features(node_uhi PRIVATE cxx_std_17)
target_link_libraries(node_uhi PRIVATE zedutils_library)
	
# Node - User
add_executable(node_user node_user.cpp)
target_compile_features(node_user PRIVATE cxx_std_17)
target_link_libraries(node_user PRIVATE zedutils_library) 

# Node - ZED
add_executable(node_zed node_zed.cpp)
target_compile_features(node_zed PRIVATE cxx_std_17)
target_link_libraries(node_zed PRIVATE zedutils_library)

# Sandbox
add_executable(sandbox sandbox.cpp)
target_compile_features(sandbox PRIVATE cxx_std_17)
target_link_libraries(sandbox PRIVATE 
	zedutils_library 
	glad_library)

# Test - Hello world
add_executable(test_hello_world test_hello_world.cpp)
target_compile_features(test_hello_world PRIVATE cxx_std_17)
target_link_libraries(test_hello_world PRIVATE zedutils_library 
	Boost::program_options)

# Test - Serialization
add_executable(test_serialization test_serialization.cpp)
target_compile_features(test_serialization PRIVATE cxx_std_17)
target_link_libraries(test_serialization PRIVATE zedutils_library)

# Test - UHI
add_executable(test_uhi test_uhi.cpp)
target_compile_features(test_uhi PRIVATE cxx_std_17)
target_link_libraries(test_uhi PRIVATE zedutils_library)
	
# Test - User
add_executable(test_user test_user.cpp)
target_compile_features(test_user PRIVATE cxx_std_17)
target_link_libraries(test_user PRIVATE zedutils_library)

# Test - ZED
add_executable(test_zed test_zed.cpp)
target_compile_features(test_zed PRIVATE cxx_std_17)
target_link_libraries(test_zed PRIVATE zedutils_library 
	Boost::program_options)

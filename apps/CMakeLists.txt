# Sandbox
add_executable(sandbox sandbox.cpp)
target_compile_features(sandbox PRIVATE cxx_std_17)
target_link_libraries(sandbox PRIVATE 
	sennet
	)

# Test - ZED
add_executable(test_zed test_zed.cpp)
target_compile_features(test_zed PRIVATE cxx_std_17)
target_link_libraries(test_zed PRIVATE 
	sennet
	Boost::program_options
	)

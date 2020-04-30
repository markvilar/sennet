# ZEDclient
add_executable(client client.cpp)
target_compile_features(client PRIVATE cxx_std_17)
target_link_libraries(client PRIVATE zedutils_library)
	
# ZEDserver
add_executable(server server.cpp)
target_compile_features(server PRIVATE cxx_std_17)
target_link_libraries(server PRIVATE zedutils_library) 

# test_client
add_executable(test_client test_client.cpp)
target_compile_features(test_client PRIVATE cxx_std_17)
target_link_libraries(test_client PRIVATE zedutils_library)

# test_serialization
add_executable(test_serialization test_serialization.cpp)
target_compile_features(test_serialization PRIVATE cxx_std_17)
target_link_libraries(test_serialization PRIVATE zedutils_library)
	
# test_server
add_executable(test_server test_server.cpp)
target_compile_features(test_server PRIVATE cxx_std_17)
target_link_libraries(test_server PRIVATE zedutils_library)

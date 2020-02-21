# server
add_executable(server server.cpp)
target_compile_features(server PRIVATE cxx_std_17)
target_link_libraries(server 
	PRIVATE 
	ZEDutils_library
	Boost::chrono
	Boost::thread)

# ZEDlisten
add_executable(ZEDlisten ZEDlisten.cpp)
target_compile_features(ZEDlisten PRIVATE cxx_std_17)
target_link_libraries(ZEDlisten 
	PRIVATE 
	ZEDutils_library)


# ZEDserver
add_executable(ZEDserver ZEDserver.cpp)
target_compile_features(ZEDserver PRIVATE cxx_std_17)
target_link_libraries(ZEDserver 
	PRIVATE 
	ZEDutils_library)


# ZEDstream
add_executable(ZEDstream ZEDstream.cpp)
target_compile_features(ZEDstream PRIVATE cxx_std_17)
target_link_libraries(ZEDstream 
	PRIVATE 
	ZEDutils_library)

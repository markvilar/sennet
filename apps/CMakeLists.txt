# ZEDserver
add_executable(ZEDserver ZEDserver.cpp)
target_compile_features(ZEDserver PRIVATE cxx_std_17)
target_link_libraries(ZEDserver PRIVATE 
	ZEDutils_library 
	dyad_library)

# ZEDstream
add_executable(ZEDstream ZEDstream.cpp)
target_compile_features(ZEDstream PRIVATE cxx_std_17)
target_link_libraries(ZEDstream PRIVATE ZEDutils_library)

# ZEDlisten
add_executable(ZEDlisten ZEDlisten.cpp)
target_compile_features(ZEDlisten PRIVATE cxx_std_17)
target_link_libraries(ZEDlisten PRIVATE ZEDutils_library)

# ZEDclient
add_executable(ZEDclient ZEDclient.cpp)
target_compile_features(ZEDclient PRIVATE cxx_std_17)
target_link_libraries(ZEDclient PRIVATE ZEDutils_library Boost::thread   
	${ZED_LIBS})

# ZEDlisten
add_executable(ZEDlisten ZEDlisten.cpp)
target_compile_features(ZEDlisten PRIVATE cxx_std_17)
target_link_libraries(ZEDlisten PRIVATE ZEDutils_library ${ZED_LIBS})

# ZEDserver
add_executable(ZEDserver ZEDserver.cpp)
target_compile_features(ZEDserver PRIVATE cxx_std_17)
target_link_libraries(ZEDserver PRIVATE boostnet_library ZEDutils_library 
	Boost::thread ${ZED_LIBS})

# ZEDstream
add_executable(ZEDstream ZEDstream.cpp)
target_compile_features(ZEDstream PRIVATE cxx_std_17)
target_link_libraries(ZEDstream PRIVATE ZEDutils_library ${ZED_LIBS})

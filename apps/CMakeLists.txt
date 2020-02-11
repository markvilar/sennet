# ZEDrecord
add_executable(ZEDrecord ZEDrecord.cpp)
target_compile_features(ZEDrecord PRIVATE cxx_std_17)
target_link_libraries(ZEDrecord PRIVATE ZEDutils_library)

# ZEDcalibrate
add_executable(ZEDcalibrate ZEDcalibrate.cpp)
target_compile_features(ZEDcalibrate PRIVATE cxx_std_17)
target_link_libraries(ZEDcalibrate PRIVATE ZEDutils_library)

# ZEDbroadcast
add_executable(ZEDbroadcast ZEDbroadcast.cpp)
target_compile_features(ZEDbroadcast PRIVATE cxx_std_17)
target_link_libraries(ZEDbroadcast PRIVATE ZEDutils_library)

# ZEDlivefeed
add_executable(ZEDlivefeed ZEDlivefeed.cpp)
target_compile_features(ZEDlivefeed PRIVATE cxx_std_17)
target_link_libraries(ZEDlivefeed PRIVATE ZEDutils_library)

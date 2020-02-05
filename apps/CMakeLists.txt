# zedrecord
add_executable(ZEDrecord ZEDrecord.cpp)
target_compile_features(ZEDrecord PRIVATE cxx_std_17)
target_link_libraries(ZEDrecord PRIVATE ZEDutils_library)

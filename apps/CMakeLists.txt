# zedrecord
add_executable(zedrecord zedrecord.cpp)
target_compile_features(zedrecord PRIVATE cxx_std_17)
target_link_libraries(zedrecord PRIVATE zedutils_library)

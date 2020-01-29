# zed_record
add_executable(zed_record zed_record.cpp)
target_compile_features(zed_record PRIVATE cxx_std_17)
target_link_libraries(zed_record PRIVATE zed_utils_library)

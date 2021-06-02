# Editor
add_executable(Editor Editor.cpp)
target_compile_definitions(Editor PRIVATE)
target_compile_features(Editor PRIVATE cxx_std_17)
target_link_libraries(Editor PRIVATE Sennet-Editor Sennet)

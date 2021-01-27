# Client
add_executable(Client Client.cpp)
target_compile_features(Client PRIVATE cxx_std_17)
target_link_libraries(Client PRIVATE Sennet)

# Client
add_executable(Editor Editor.cpp)
target_compile_features(Editor PRIVATE cxx_std_17)
target_link_libraries(Editor PRIVATE Sennet Sennet-Editor)

# Server
add_executable(Server Server.cpp)
target_compile_features(Server PRIVATE cxx_std_17)
target_link_libraries(Server PRIVATE Sennet)

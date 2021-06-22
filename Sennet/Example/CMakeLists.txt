# Client
add_executable(Client Client.cpp)
target_compile_features(Client PRIVATE cxx_std_17)
target_compile_definitions(Client PRIVATE)
target_link_libraries(Client PRIVATE Sennet)

# Server
add_executable(Server Server.cpp)
target_compile_features(Server PRIVATE cxx_std_17)
target_compile_definitions(Server PRIVATE)
target_link_libraries(Server PRIVATE Sennet)

# HTTPServer
add_executable(HTTPServer HTTPServer.cpp)
target_compile_features(HTTPServer PRIVATE cxx_std_17)
target_compile_definitions(HTTPServer PRIVATE)
target_link_libraries(HTTPServer PRIVATE Sennet)

# TCPClient
add_executable(TCPClient TCPClient.cpp)
target_compile_features(TCPClient PRIVATE cxx_std_17)
target_compile_definitions(TCPClient PRIVATE)
target_link_libraries(TCPClient PRIVATE Sennet)

# TCPServer
add_executable(TCPServer TCPServer.cpp)
target_compile_features(TCPServer PRIVATE cxx_std_17)
target_compile_definitions(TCPServer PRIVATE)
target_link_libraries(TCPServer PRIVATE Sennet)

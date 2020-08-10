# Client
add_executable(Client Client.cpp)
target_compile_features(Client PRIVATE cxx_std_17)
target_link_libraries(Client PRIVATE Sennet)

# Sandbox
add_executable(Sandbox Sandbox.cpp)
target_compile_features(Sandbox PRIVATE cxx_std_17)
target_link_libraries(Sandbox PRIVATE Sennet)

# SandboxApplication
add_executable(SandboxApplication SandboxApplication.cpp)
target_compile_features(SandboxApplication PRIVATE cxx_std_17)
target_link_libraries(SandboxApplication PRIVATE Sennet)

# Serialization
add_executable(Serialization Serialization.cpp)
target_compile_features(Serialization PRIVATE cxx_std_17)
target_link_libraries(Serialization PRIVATE Sennet)

# Server
add_executable(Server Server.cpp)
target_compile_features(Server PRIVATE cxx_std_17)
target_link_libraries(Server PRIVATE Sennet)

# ZEDControl
add_executable(ZEDControl ZEDControl.cpp)
target_compile_features(ZEDControl PRIVATE cxx_std_17)
target_link_libraries(ZEDControl PRIVATE Sennet)

# ZEDNode
add_executable(ZEDNode ZEDNode.cpp)
target_compile_features(ZEDNode PRIVATE cxx_std_17)
target_link_libraries(ZEDNode PRIVATE Sennet)

# ZEDSandbox
add_executable(ZEDSandbox ZEDSandbox.cpp)
target_compile_features(ZEDSandbox PRIVATE cxx_std_17)
target_link_libraries(ZEDSandbox PRIVATE Sennet)

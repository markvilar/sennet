# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/Client.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/ZEDController.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/ZEDio.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/ZEDListener.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/ZEDRecorder.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/ZEDStreamer.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(ZEDutils_library 
	Client.cpp
	ZEDController.cpp
	ZEDio.cpp 
	ZEDListener.cpp
	ZEDRecorder.cpp
	ZEDStreamer.cpp
	${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(ZEDutils_library 
	PUBLIC 
	../include 
	${Boost_INCLUDE_DIRS}
	${CUDA_INCLUDE_DIRS}
	${ZED_INCLUDE_DIRS})

# This depends on ZED
target_link_libraries(ZEDutils_library 
	PRIVATE 
	${ZED_LIBS})

# All users of this will need at least C++17
target_compile_features(ZEDutils_library PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
	TREE "${PROJECT_SOURCE_DIR}/include" 
	PREFIX "Header Files" 
	FILES ${HEADER_LIST}
)

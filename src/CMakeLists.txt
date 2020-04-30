# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/active_messaging/Action.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/active_messaging/Connection.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/active_messaging/Runtime.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/io.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/network.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/types.hpp"
	"${PROJECT_SOURCE_DIR}/include/ZEDutils/serialization.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(zedutils_library 
	active_messaging/Action.cpp 
	active_messaging/Connection.cpp 
	active_messaging/Runtime.cpp 
	io.cpp 
	network.cpp 
	types.cpp 
	serialization.cpp
	${HEADER_LIST})
	
# We need these directories, and users of our library will need it too
target_include_directories(zedutils_library PUBLIC ../include 
	${Boost_INCLUDE_DIRS} ${CUDA_INCLUDE_DIRS} ${ZED_INCLUDE_DIRS}) 
		
# This depends on ZED and Boost
target_link_libraries(zedutils_library PRIVATE ${ZED_LIBS} Boost::thread) 

# All users of this will need at least C++17
target_compile_features(zedutils_library PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES
	${HEADER_LIST})

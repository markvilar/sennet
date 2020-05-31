# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/hello_world.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/request.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/response.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/sleep.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/zed_close.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/zed_get_settings.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/zed_image.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/zed_open.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/zed_retrieve.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/zed_settings.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/zed_start_record.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/actions/zed_stop_record.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/container_device.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/am/core.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/io.hpp"
	"${PROJECT_SOURCE_DIR}/include/zedutils/serialization.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(zedutils_library 
	am/core.cpp 
	io.cpp 
	${HEADER_LIST})
	
# We need these directories, and users of our library will need it too
target_include_directories(zedutils_library PUBLIC 
	../include 
	${Boost_INCLUDE_DIRS} 
	${CUDA_INCLUDE_DIRS} 
	${ZED_INCLUDE_DIRS}) 
		
# This depends on ZED and Boost
target_link_libraries(zedutils_library PRIVATE 
	${ZED_LIBS} 
	Boost::serialization
	Boost::thread) 

# All users of this will need at least C++17
target_compile_features(zedutils_library PUBLIC 
	cxx_std_17)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES
	${HEADER_LIST})

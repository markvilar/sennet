# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/sennet/am/actions.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/am/container_device.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/am/core.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/handlers/handler.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/handlers/zed_recorder.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/types/zed.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/conversion/zed.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/application.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/io.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/log.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/serialization.hpp"
	)



# Make an automatic library - will be static or dynamic based on user setting
add_library(sennet
	am/core.cpp 
	handlers/zed_recorder.cpp
	types/zed.cpp
	conversion/zed.cpp
	application.cpp
	io.cpp 
	log.cpp
	${HEADER_LIST}
	)
	
# Include headers and source code from other libraries in zedutils. This way we
# won't have to link all of zedutils dependencies into targets that use
# zedutils, but just zedutils library.
target_include_directories(sennet PUBLIC 
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/extern/spdlog/include"
	${Boost_INCLUDE_DIRS} 
	${CUDA_INCLUDE_DIRS} 
	${ZED_INCLUDE_DIRS}
	) 
		
# This depends on ZED and Boost features that needs to be linked to the library.
target_link_libraries(sennet PRIVATE 
	Boost::serialization
	Boost::thread
	${ZED_LIBS}
	) 

# All users of this will need at least C++17
target_compile_features(sennet PUBLIC 
	cxx_std_17
	)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES
	${HEADER_LIST})

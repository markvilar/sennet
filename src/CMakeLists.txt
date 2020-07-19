# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/sennet/sennet.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/am/actions.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/am/container_device.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/am/core.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/application.hpp"	
	"${PROJECT_SOURCE_DIR}/include/sennet/core/base.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/handler.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/log.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/core/window.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/events/event.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/platform/windows_window.hpp"	
	"${PROJECT_SOURCE_DIR}/include/sennet/types/basic_types.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/types/zed.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/zed/conversion.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/zed/io.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/zed/serialization.hpp"
	"${PROJECT_SOURCE_DIR}/include/sennet/zed/zed_recorder.hpp"
	)



# Make an automatic library - will be static or dynamic based on user setting
add_library(sennet
	am/core.cpp 
	core/application.cpp
	core/log.cpp
	core/window.cpp
	events/event.cpp
	platform/windows_window.cpp
	types/basic_types.cpp
	types/zed.cpp
	zed/conversion.cpp
	zed/io.cpp 
	zed/zed_recorder.cpp
	${HEADER_LIST}
	)
	
# Include headers and source code from other libraries in sennet. This way we
# won't have to link all of sennet dependencies into targets that use
# sennet, but just sennet library.
# TODO: Add glfw and imgui include paths.
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

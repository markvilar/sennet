# Headers
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/zedutils/zederrors.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(zedutils_library zederrors.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(zedutils_library PUBLIC ../include ${ZED_INCLUDE_DIRS} ${CUDA_INCLUDE_DIRS})

# This depends on ZED
target_link_libraries(zedutils_library PRIVATE ${ZED_LIBS})

# All users of this will need at least C++17
target_compile_features(zedutils_library PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
	TREE "${PROJECT_SOURCE_DIR}/include" 
	PREFIX "Header Files" 
	FILES ${HEADER_LIST}
)

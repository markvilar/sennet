# Headers
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/zed_utils/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(zed_utils_library lib.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(zed_utils_library PUBLIC ../include)

# This depends on ZED
target_link_libraries(zed_utils_library PRIVATE ${ZED_LIBS})

# All users of this will need at least C++17
target_compile_features(zed_utils_library PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
	TREE "${PROJECT_SOURCE_DIR}/include" 
	PREFIX "Header Files" 
	FILES ${HEADER_LIST}
)

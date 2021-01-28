# Headers
set(HEADER_LIST 
	"${PROJECT_SOURCE_DIR}/include/glad/glad.h"
	"${PROJECT_SOURCE_DIR}/include/KHR/khrplatform.h"
	)

# Make an automatic library - will be static or dynamic based on user setting
add_library(glad
	glad.c
	${HEADER_LIST})
	
# We need these directories, and users of our library will need it too
target_include_directories(glad PUBLIC 
	"${PROJECT_SOURCE_DIR}/include"
	)

# glad doesn't depend on anything.
target_link_libraries(glad PRIVATE )

# TODO: Check what C++ version glad needs to compiler.
target_compile_features(glad PUBLIC )

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES
	${HEADER_LIST})

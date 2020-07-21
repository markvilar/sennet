if(NOT SETUP_CONFIGURATIONS_DONE)
	set(SETUP_CONFIGURATIONS_DONE TRUE)

	get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
	if(isMultiConfig)
		set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile" CACHE
			STRING "" FORCE)
	else()
		if(NOT CMAKE_BUILD_TYPE)
			message("Defaulting to debug build.")
			set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
		endif()
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose
			the type of build.")
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
			"Debug;Release;Profile")
	endif()
	# TODO: Add profiles.
	set(CMAKE_C_FLAGS_PROFILE "...")
	set(CMAKE_CXX_FLAGS_PROFILE "...")
	set(CMAKE_EXE_LINKER_FLAGS_PROFILE "...")
endif()

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake-3.16.2-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.16.2-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/martin/dev/zed_gym

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/martin/dev/zed_gym/build

# Include any dependencies generated for this target.
include CMakeFiles/zed_application.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zed_application.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zed_application.dir/flags.make

CMakeFiles/zed_application.dir/src/main.cpp.o: CMakeFiles/zed_application.dir/flags.make
CMakeFiles/zed_application.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/martin/dev/zed_gym/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/zed_application.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/zed_application.dir/src/main.cpp.o -c /home/martin/dev/zed_gym/src/main.cpp

CMakeFiles/zed_application.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/zed_application.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/martin/dev/zed_gym/src/main.cpp > CMakeFiles/zed_application.dir/src/main.cpp.i

CMakeFiles/zed_application.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/zed_application.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/martin/dev/zed_gym/src/main.cpp -o CMakeFiles/zed_application.dir/src/main.cpp.s

# Object files for target zed_application
zed_application_OBJECTS = \
"CMakeFiles/zed_application.dir/src/main.cpp.o"

# External object files for target zed_application
zed_application_EXTERNAL_OBJECTS =

zed_application: CMakeFiles/zed_application.dir/src/main.cpp.o
zed_application: CMakeFiles/zed_application.dir/build.make
zed_application: /usr/local/zed/lib/libsl_input.so
zed_application: /usr/local/zed/lib/libsl_core.so
zed_application: /usr/local/zed/lib/libsl_zed.so
zed_application: /usr/lib/libopenblas.so
zed_application: /usr/lib/x86_64-linux-gnu/libcuda.so
zed_application: /usr/local/cuda/lib64/libcudart.so
zed_application: /usr/local/cuda-10.0/lib64/libnppial.so
zed_application: /usr/local/cuda-10.0/lib64/libnppisu.so
zed_application: /usr/local/cuda-10.0/lib64/libnppicc.so
zed_application: /usr/local/cuda-10.0/lib64/libnppicom.so
zed_application: /usr/local/cuda-10.0/lib64/libnppidei.so
zed_application: /usr/local/cuda-10.0/lib64/libnppif.so
zed_application: /usr/local/cuda-10.0/lib64/libnppig.so
zed_application: /usr/local/cuda-10.0/lib64/libnppim.so
zed_application: /usr/local/cuda-10.0/lib64/libnppist.so
zed_application: /usr/local/cuda-10.0/lib64/libnppitc.so
zed_application: /usr/local/cuda-10.0/lib64/libcublas.so
zed_application: /usr/local/cuda-10.0/lib64/libcurand.so
zed_application: /usr/local/cuda-10.0/lib64/libcublas.so
zed_application: /usr/local/cuda-10.0/lib64/libcurand.so
zed_application: /usr/local/cuda/lib64/libnpps.so
zed_application: CMakeFiles/zed_application.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/martin/dev/zed_gym/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable zed_application"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zed_application.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zed_application.dir/build: zed_application

.PHONY : CMakeFiles/zed_application.dir/build

CMakeFiles/zed_application.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zed_application.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zed_application.dir/clean

CMakeFiles/zed_application.dir/depend:
	cd /home/martin/dev/zed_gym/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/martin/dev/zed_gym /home/martin/dev/zed_gym /home/martin/dev/zed_gym/build /home/martin/dev/zed_gym/build /home/martin/dev/zed_gym/build/CMakeFiles/zed_application.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zed_application.dir/depend


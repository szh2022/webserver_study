# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/webserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/webserver/build/Debug

# Include any dependencies generated for this target.
include WebServer/base/tests/CMakeFiles/LoggingTest.dir/depend.make

# Include the progress variables for this target.
include WebServer/base/tests/CMakeFiles/LoggingTest.dir/progress.make

# Include the compile flags for this target's objects.
include WebServer/base/tests/CMakeFiles/LoggingTest.dir/flags.make

WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o: WebServer/base/tests/CMakeFiles/LoggingTest.dir/flags.make
WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o: ../../WebServer/base/tests/LoggingTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/webserver/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o"
	cd /root/webserver/build/Debug/WebServer/base/tests && g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o -c /root/webserver/WebServer/base/tests/LoggingTest.cpp

WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoggingTest.dir/LoggingTest.cpp.i"
	cd /root/webserver/build/Debug/WebServer/base/tests && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/webserver/WebServer/base/tests/LoggingTest.cpp > CMakeFiles/LoggingTest.dir/LoggingTest.cpp.i

WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoggingTest.dir/LoggingTest.cpp.s"
	cd /root/webserver/build/Debug/WebServer/base/tests && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/webserver/WebServer/base/tests/LoggingTest.cpp -o CMakeFiles/LoggingTest.dir/LoggingTest.cpp.s

WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o.requires:

.PHONY : WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o.requires

WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o.provides: WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o.requires
	$(MAKE) -f WebServer/base/tests/CMakeFiles/LoggingTest.dir/build.make WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o.provides.build
.PHONY : WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o.provides

WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o.provides.build: WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o


# Object files for target LoggingTest
LoggingTest_OBJECTS = \
"CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o"

# External object files for target LoggingTest
LoggingTest_EXTERNAL_OBJECTS =

WebServer/base/tests/LoggingTest: WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o
WebServer/base/tests/LoggingTest: WebServer/base/tests/CMakeFiles/LoggingTest.dir/build.make
WebServer/base/tests/LoggingTest: WebServer/base/libserver_base.a
WebServer/base/tests/LoggingTest: WebServer/base/tests/CMakeFiles/LoggingTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/webserver/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LoggingTest"
	cd /root/webserver/build/Debug/WebServer/base/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LoggingTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
WebServer/base/tests/CMakeFiles/LoggingTest.dir/build: WebServer/base/tests/LoggingTest

.PHONY : WebServer/base/tests/CMakeFiles/LoggingTest.dir/build

WebServer/base/tests/CMakeFiles/LoggingTest.dir/requires: WebServer/base/tests/CMakeFiles/LoggingTest.dir/LoggingTest.cpp.o.requires

.PHONY : WebServer/base/tests/CMakeFiles/LoggingTest.dir/requires

WebServer/base/tests/CMakeFiles/LoggingTest.dir/clean:
	cd /root/webserver/build/Debug/WebServer/base/tests && $(CMAKE_COMMAND) -P CMakeFiles/LoggingTest.dir/cmake_clean.cmake
.PHONY : WebServer/base/tests/CMakeFiles/LoggingTest.dir/clean

WebServer/base/tests/CMakeFiles/LoggingTest.dir/depend:
	cd /root/webserver/build/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/webserver /root/webserver/WebServer/base/tests /root/webserver/build/Debug /root/webserver/build/Debug/WebServer/base/tests /root/webserver/build/Debug/WebServer/base/tests/CMakeFiles/LoggingTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : WebServer/base/tests/CMakeFiles/LoggingTest.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /Users/Herman/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Users/Herman/Desktop/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Herman/Desktop/Projects/TystServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Herman/Desktop/Projects/TystServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TystServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TystServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TystServer.dir/flags.make

CMakeFiles/TystServer.dir/main.c.o: CMakeFiles/TystServer.dir/flags.make
CMakeFiles/TystServer.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Herman/Desktop/Projects/TystServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TystServer.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TystServer.dir/main.c.o   -c /Users/Herman/Desktop/Projects/TystServer/main.c

CMakeFiles/TystServer.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TystServer.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Herman/Desktop/Projects/TystServer/main.c > CMakeFiles/TystServer.dir/main.c.i

CMakeFiles/TystServer.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TystServer.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Herman/Desktop/Projects/TystServer/main.c -o CMakeFiles/TystServer.dir/main.c.s

# Object files for target TystServer
TystServer_OBJECTS = \
"CMakeFiles/TystServer.dir/main.c.o"

# External object files for target TystServer
TystServer_EXTERNAL_OBJECTS =

TystServer: CMakeFiles/TystServer.dir/main.c.o
TystServer: CMakeFiles/TystServer.dir/build.make
TystServer: CMakeFiles/TystServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Herman/Desktop/Projects/TystServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TystServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TystServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TystServer.dir/build: TystServer

.PHONY : CMakeFiles/TystServer.dir/build

CMakeFiles/TystServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TystServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TystServer.dir/clean

CMakeFiles/TystServer.dir/depend:
	cd /Users/Herman/Desktop/Projects/TystServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Herman/Desktop/Projects/TystServer /Users/Herman/Desktop/Projects/TystServer /Users/Herman/Desktop/Projects/TystServer/cmake-build-debug /Users/Herman/Desktop/Projects/TystServer/cmake-build-debug /Users/Herman/Desktop/Projects/TystServer/cmake-build-debug/CMakeFiles/TystServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TystServer.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/gand/Programs/clion-2017.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/gand/Programs/clion-2017.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gand/Documents/sphere/threads/output/01-allocator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gand/Documents/sphere/threads/output/01-allocator/cmake-build-debug

# Utility rule file for 01_allocator.

# Include the progress variables for this target.
include CMakeFiles/01_allocator.dir/progress.make

CMakeFiles/01_allocator:
	make -C /home/gand/Documents/sphere/threads/output/01-allocator CLION_EXE_DIR=/home/gand/Documents/sphere/threads/output/01-allocator/cmake-build-debug

01_allocator: CMakeFiles/01_allocator
01_allocator: CMakeFiles/01_allocator.dir/build.make

.PHONY : 01_allocator

# Rule to build all files generated by this target.
CMakeFiles/01_allocator.dir/build: 01_allocator

.PHONY : CMakeFiles/01_allocator.dir/build

CMakeFiles/01_allocator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/01_allocator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/01_allocator.dir/clean

CMakeFiles/01_allocator.dir/depend:
	cd /home/gand/Documents/sphere/threads/output/01-allocator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gand/Documents/sphere/threads/output/01-allocator /home/gand/Documents/sphere/threads/output/01-allocator /home/gand/Documents/sphere/threads/output/01-allocator/cmake-build-debug /home/gand/Documents/sphere/threads/output/01-allocator/cmake-build-debug /home/gand/Documents/sphere/threads/output/01-allocator/cmake-build-debug/CMakeFiles/01_allocator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/01_allocator.dir/depend


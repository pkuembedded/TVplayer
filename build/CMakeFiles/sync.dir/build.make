# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/infinite/Project/TVplayer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/infinite/Project/TVplayer/build

# Include any dependencies generated for this target.
include CMakeFiles/sync.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sync.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sync.dir/flags.make

CMakeFiles/sync.dir/src/sync.c.o: CMakeFiles/sync.dir/flags.make
CMakeFiles/sync.dir/src/sync.c.o: ../src/sync.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/infinite/Project/TVplayer/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/sync.dir/src/sync.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/sync.dir/src/sync.c.o   -c /home/infinite/Project/TVplayer/src/sync.c

CMakeFiles/sync.dir/src/sync.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sync.dir/src/sync.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/infinite/Project/TVplayer/src/sync.c > CMakeFiles/sync.dir/src/sync.c.i

CMakeFiles/sync.dir/src/sync.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sync.dir/src/sync.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/infinite/Project/TVplayer/src/sync.c -o CMakeFiles/sync.dir/src/sync.c.s

CMakeFiles/sync.dir/src/sync.c.o.requires:
.PHONY : CMakeFiles/sync.dir/src/sync.c.o.requires

CMakeFiles/sync.dir/src/sync.c.o.provides: CMakeFiles/sync.dir/src/sync.c.o.requires
	$(MAKE) -f CMakeFiles/sync.dir/build.make CMakeFiles/sync.dir/src/sync.c.o.provides.build
.PHONY : CMakeFiles/sync.dir/src/sync.c.o.provides

CMakeFiles/sync.dir/src/sync.c.o.provides.build: CMakeFiles/sync.dir/src/sync.c.o

# Object files for target sync
sync_OBJECTS = \
"CMakeFiles/sync.dir/src/sync.c.o"

# External object files for target sync
sync_EXTERNAL_OBJECTS =

libsync.so: CMakeFiles/sync.dir/src/sync.c.o
libsync.so: CMakeFiles/sync.dir/build.make
libsync.so: CMakeFiles/sync.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libsync.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sync.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sync.dir/build: libsync.so
.PHONY : CMakeFiles/sync.dir/build

CMakeFiles/sync.dir/requires: CMakeFiles/sync.dir/src/sync.c.o.requires
.PHONY : CMakeFiles/sync.dir/requires

CMakeFiles/sync.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sync.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sync.dir/clean

CMakeFiles/sync.dir/depend:
	cd /home/infinite/Project/TVplayer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/infinite/Project/TVplayer /home/infinite/Project/TVplayer /home/infinite/Project/TVplayer/build /home/infinite/Project/TVplayer/build /home/infinite/Project/TVplayer/build/CMakeFiles/sync.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sync.dir/depend

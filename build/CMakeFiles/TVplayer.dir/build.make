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
include CMakeFiles/TVplayer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TVplayer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TVplayer.dir/flags.make

CMakeFiles/TVplayer.dir/src/queue.c.o: CMakeFiles/TVplayer.dir/flags.make
CMakeFiles/TVplayer.dir/src/queue.c.o: ../src/queue.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/infinite/Project/TVplayer/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/TVplayer.dir/src/queue.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/TVplayer.dir/src/queue.c.o   -c /home/infinite/Project/TVplayer/src/queue.c

CMakeFiles/TVplayer.dir/src/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TVplayer.dir/src/queue.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/infinite/Project/TVplayer/src/queue.c > CMakeFiles/TVplayer.dir/src/queue.c.i

CMakeFiles/TVplayer.dir/src/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TVplayer.dir/src/queue.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/infinite/Project/TVplayer/src/queue.c -o CMakeFiles/TVplayer.dir/src/queue.c.s

CMakeFiles/TVplayer.dir/src/queue.c.o.requires:
.PHONY : CMakeFiles/TVplayer.dir/src/queue.c.o.requires

CMakeFiles/TVplayer.dir/src/queue.c.o.provides: CMakeFiles/TVplayer.dir/src/queue.c.o.requires
	$(MAKE) -f CMakeFiles/TVplayer.dir/build.make CMakeFiles/TVplayer.dir/src/queue.c.o.provides.build
.PHONY : CMakeFiles/TVplayer.dir/src/queue.c.o.provides

CMakeFiles/TVplayer.dir/src/queue.c.o.provides.build: CMakeFiles/TVplayer.dir/src/queue.c.o

CMakeFiles/TVplayer.dir/src/video.c.o: CMakeFiles/TVplayer.dir/flags.make
CMakeFiles/TVplayer.dir/src/video.c.o: ../src/video.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/infinite/Project/TVplayer/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/TVplayer.dir/src/video.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/TVplayer.dir/src/video.c.o   -c /home/infinite/Project/TVplayer/src/video.c

CMakeFiles/TVplayer.dir/src/video.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TVplayer.dir/src/video.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/infinite/Project/TVplayer/src/video.c > CMakeFiles/TVplayer.dir/src/video.c.i

CMakeFiles/TVplayer.dir/src/video.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TVplayer.dir/src/video.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/infinite/Project/TVplayer/src/video.c -o CMakeFiles/TVplayer.dir/src/video.c.s

CMakeFiles/TVplayer.dir/src/video.c.o.requires:
.PHONY : CMakeFiles/TVplayer.dir/src/video.c.o.requires

CMakeFiles/TVplayer.dir/src/video.c.o.provides: CMakeFiles/TVplayer.dir/src/video.c.o.requires
	$(MAKE) -f CMakeFiles/TVplayer.dir/build.make CMakeFiles/TVplayer.dir/src/video.c.o.provides.build
.PHONY : CMakeFiles/TVplayer.dir/src/video.c.o.provides

CMakeFiles/TVplayer.dir/src/video.c.o.provides.build: CMakeFiles/TVplayer.dir/src/video.c.o

CMakeFiles/TVplayer.dir/src/display.c.o: CMakeFiles/TVplayer.dir/flags.make
CMakeFiles/TVplayer.dir/src/display.c.o: ../src/display.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/infinite/Project/TVplayer/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/TVplayer.dir/src/display.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/TVplayer.dir/src/display.c.o   -c /home/infinite/Project/TVplayer/src/display.c

CMakeFiles/TVplayer.dir/src/display.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TVplayer.dir/src/display.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/infinite/Project/TVplayer/src/display.c > CMakeFiles/TVplayer.dir/src/display.c.i

CMakeFiles/TVplayer.dir/src/display.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TVplayer.dir/src/display.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/infinite/Project/TVplayer/src/display.c -o CMakeFiles/TVplayer.dir/src/display.c.s

CMakeFiles/TVplayer.dir/src/display.c.o.requires:
.PHONY : CMakeFiles/TVplayer.dir/src/display.c.o.requires

CMakeFiles/TVplayer.dir/src/display.c.o.provides: CMakeFiles/TVplayer.dir/src/display.c.o.requires
	$(MAKE) -f CMakeFiles/TVplayer.dir/build.make CMakeFiles/TVplayer.dir/src/display.c.o.provides.build
.PHONY : CMakeFiles/TVplayer.dir/src/display.c.o.provides

CMakeFiles/TVplayer.dir/src/display.c.o.provides.build: CMakeFiles/TVplayer.dir/src/display.c.o

CMakeFiles/TVplayer.dir/src/TVplayer.c.o: CMakeFiles/TVplayer.dir/flags.make
CMakeFiles/TVplayer.dir/src/TVplayer.c.o: ../src/TVplayer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/infinite/Project/TVplayer/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/TVplayer.dir/src/TVplayer.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/TVplayer.dir/src/TVplayer.c.o   -c /home/infinite/Project/TVplayer/src/TVplayer.c

CMakeFiles/TVplayer.dir/src/TVplayer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TVplayer.dir/src/TVplayer.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/infinite/Project/TVplayer/src/TVplayer.c > CMakeFiles/TVplayer.dir/src/TVplayer.c.i

CMakeFiles/TVplayer.dir/src/TVplayer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TVplayer.dir/src/TVplayer.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/infinite/Project/TVplayer/src/TVplayer.c -o CMakeFiles/TVplayer.dir/src/TVplayer.c.s

CMakeFiles/TVplayer.dir/src/TVplayer.c.o.requires:
.PHONY : CMakeFiles/TVplayer.dir/src/TVplayer.c.o.requires

CMakeFiles/TVplayer.dir/src/TVplayer.c.o.provides: CMakeFiles/TVplayer.dir/src/TVplayer.c.o.requires
	$(MAKE) -f CMakeFiles/TVplayer.dir/build.make CMakeFiles/TVplayer.dir/src/TVplayer.c.o.provides.build
.PHONY : CMakeFiles/TVplayer.dir/src/TVplayer.c.o.provides

CMakeFiles/TVplayer.dir/src/TVplayer.c.o.provides.build: CMakeFiles/TVplayer.dir/src/TVplayer.c.o

CMakeFiles/TVplayer.dir/src/sync.c.o: CMakeFiles/TVplayer.dir/flags.make
CMakeFiles/TVplayer.dir/src/sync.c.o: ../src/sync.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/infinite/Project/TVplayer/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/TVplayer.dir/src/sync.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/TVplayer.dir/src/sync.c.o   -c /home/infinite/Project/TVplayer/src/sync.c

CMakeFiles/TVplayer.dir/src/sync.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TVplayer.dir/src/sync.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/infinite/Project/TVplayer/src/sync.c > CMakeFiles/TVplayer.dir/src/sync.c.i

CMakeFiles/TVplayer.dir/src/sync.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TVplayer.dir/src/sync.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/infinite/Project/TVplayer/src/sync.c -o CMakeFiles/TVplayer.dir/src/sync.c.s

CMakeFiles/TVplayer.dir/src/sync.c.o.requires:
.PHONY : CMakeFiles/TVplayer.dir/src/sync.c.o.requires

CMakeFiles/TVplayer.dir/src/sync.c.o.provides: CMakeFiles/TVplayer.dir/src/sync.c.o.requires
	$(MAKE) -f CMakeFiles/TVplayer.dir/build.make CMakeFiles/TVplayer.dir/src/sync.c.o.provides.build
.PHONY : CMakeFiles/TVplayer.dir/src/sync.c.o.provides

CMakeFiles/TVplayer.dir/src/sync.c.o.provides.build: CMakeFiles/TVplayer.dir/src/sync.c.o

CMakeFiles/TVplayer.dir/src/audio.c.o: CMakeFiles/TVplayer.dir/flags.make
CMakeFiles/TVplayer.dir/src/audio.c.o: ../src/audio.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/infinite/Project/TVplayer/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/TVplayer.dir/src/audio.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/TVplayer.dir/src/audio.c.o   -c /home/infinite/Project/TVplayer/src/audio.c

CMakeFiles/TVplayer.dir/src/audio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TVplayer.dir/src/audio.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/infinite/Project/TVplayer/src/audio.c > CMakeFiles/TVplayer.dir/src/audio.c.i

CMakeFiles/TVplayer.dir/src/audio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TVplayer.dir/src/audio.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/infinite/Project/TVplayer/src/audio.c -o CMakeFiles/TVplayer.dir/src/audio.c.s

CMakeFiles/TVplayer.dir/src/audio.c.o.requires:
.PHONY : CMakeFiles/TVplayer.dir/src/audio.c.o.requires

CMakeFiles/TVplayer.dir/src/audio.c.o.provides: CMakeFiles/TVplayer.dir/src/audio.c.o.requires
	$(MAKE) -f CMakeFiles/TVplayer.dir/build.make CMakeFiles/TVplayer.dir/src/audio.c.o.provides.build
.PHONY : CMakeFiles/TVplayer.dir/src/audio.c.o.provides

CMakeFiles/TVplayer.dir/src/audio.c.o.provides.build: CMakeFiles/TVplayer.dir/src/audio.c.o

CMakeFiles/TVplayer.dir/src/parse.c.o: CMakeFiles/TVplayer.dir/flags.make
CMakeFiles/TVplayer.dir/src/parse.c.o: ../src/parse.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/infinite/Project/TVplayer/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/TVplayer.dir/src/parse.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/TVplayer.dir/src/parse.c.o   -c /home/infinite/Project/TVplayer/src/parse.c

CMakeFiles/TVplayer.dir/src/parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TVplayer.dir/src/parse.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/infinite/Project/TVplayer/src/parse.c > CMakeFiles/TVplayer.dir/src/parse.c.i

CMakeFiles/TVplayer.dir/src/parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TVplayer.dir/src/parse.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/infinite/Project/TVplayer/src/parse.c -o CMakeFiles/TVplayer.dir/src/parse.c.s

CMakeFiles/TVplayer.dir/src/parse.c.o.requires:
.PHONY : CMakeFiles/TVplayer.dir/src/parse.c.o.requires

CMakeFiles/TVplayer.dir/src/parse.c.o.provides: CMakeFiles/TVplayer.dir/src/parse.c.o.requires
	$(MAKE) -f CMakeFiles/TVplayer.dir/build.make CMakeFiles/TVplayer.dir/src/parse.c.o.provides.build
.PHONY : CMakeFiles/TVplayer.dir/src/parse.c.o.provides

CMakeFiles/TVplayer.dir/src/parse.c.o.provides.build: CMakeFiles/TVplayer.dir/src/parse.c.o

# Object files for target TVplayer
TVplayer_OBJECTS = \
"CMakeFiles/TVplayer.dir/src/queue.c.o" \
"CMakeFiles/TVplayer.dir/src/video.c.o" \
"CMakeFiles/TVplayer.dir/src/display.c.o" \
"CMakeFiles/TVplayer.dir/src/TVplayer.c.o" \
"CMakeFiles/TVplayer.dir/src/sync.c.o" \
"CMakeFiles/TVplayer.dir/src/audio.c.o" \
"CMakeFiles/TVplayer.dir/src/parse.c.o"

# External object files for target TVplayer
TVplayer_EXTERNAL_OBJECTS =

TVplayer: CMakeFiles/TVplayer.dir/src/queue.c.o
TVplayer: CMakeFiles/TVplayer.dir/src/video.c.o
TVplayer: CMakeFiles/TVplayer.dir/src/display.c.o
TVplayer: CMakeFiles/TVplayer.dir/src/TVplayer.c.o
TVplayer: CMakeFiles/TVplayer.dir/src/sync.c.o
TVplayer: CMakeFiles/TVplayer.dir/src/audio.c.o
TVplayer: CMakeFiles/TVplayer.dir/src/parse.c.o
TVplayer: libaudio.so
TVplayer: libvideo.so
TVplayer: libparse.so
TVplayer: libsync.so
TVplayer: libqueue.so
TVplayer: libdisplay.so
TVplayer: /usr/local/lib/libSDL.so
TVplayer: CMakeFiles/TVplayer.dir/build.make
TVplayer: CMakeFiles/TVplayer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable TVplayer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TVplayer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TVplayer.dir/build: TVplayer
.PHONY : CMakeFiles/TVplayer.dir/build

CMakeFiles/TVplayer.dir/requires: CMakeFiles/TVplayer.dir/src/queue.c.o.requires
CMakeFiles/TVplayer.dir/requires: CMakeFiles/TVplayer.dir/src/video.c.o.requires
CMakeFiles/TVplayer.dir/requires: CMakeFiles/TVplayer.dir/src/display.c.o.requires
CMakeFiles/TVplayer.dir/requires: CMakeFiles/TVplayer.dir/src/TVplayer.c.o.requires
CMakeFiles/TVplayer.dir/requires: CMakeFiles/TVplayer.dir/src/sync.c.o.requires
CMakeFiles/TVplayer.dir/requires: CMakeFiles/TVplayer.dir/src/audio.c.o.requires
CMakeFiles/TVplayer.dir/requires: CMakeFiles/TVplayer.dir/src/parse.c.o.requires
.PHONY : CMakeFiles/TVplayer.dir/requires

CMakeFiles/TVplayer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TVplayer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TVplayer.dir/clean

CMakeFiles/TVplayer.dir/depend:
	cd /home/infinite/Project/TVplayer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/infinite/Project/TVplayer /home/infinite/Project/TVplayer /home/infinite/Project/TVplayer/build /home/infinite/Project/TVplayer/build /home/infinite/Project/TVplayer/build/CMakeFiles/TVplayer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TVplayer.dir/depend


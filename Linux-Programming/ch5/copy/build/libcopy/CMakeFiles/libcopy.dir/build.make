# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /usr/cmake-3.3.1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/cmake-3.3.1-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zeng/programming/Linux-Programming/ch5/copy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zeng/programming/Linux-Programming/ch5/copy/build

# Include any dependencies generated for this target.
include libcopy/CMakeFiles/libcopy.dir/depend.make

# Include the progress variables for this target.
include libcopy/CMakeFiles/libcopy.dir/progress.make

# Include the compile flags for this target's objects.
include libcopy/CMakeFiles/libcopy.dir/flags.make

libcopy/CMakeFiles/libcopy.dir/copy.o: libcopy/CMakeFiles/libcopy.dir/flags.make
libcopy/CMakeFiles/libcopy.dir/copy.o: ../libcopy/copy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zeng/programming/Linux-Programming/ch5/copy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libcopy/CMakeFiles/libcopy.dir/copy.o"
	cd /home/zeng/programming/Linux-Programming/ch5/copy/build/libcopy && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/libcopy.dir/copy.o   -c /home/zeng/programming/Linux-Programming/ch5/copy/libcopy/copy.c

libcopy/CMakeFiles/libcopy.dir/copy.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/libcopy.dir/copy.i"
	cd /home/zeng/programming/Linux-Programming/ch5/copy/build/libcopy && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/zeng/programming/Linux-Programming/ch5/copy/libcopy/copy.c > CMakeFiles/libcopy.dir/copy.i

libcopy/CMakeFiles/libcopy.dir/copy.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/libcopy.dir/copy.s"
	cd /home/zeng/programming/Linux-Programming/ch5/copy/build/libcopy && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/zeng/programming/Linux-Programming/ch5/copy/libcopy/copy.c -o CMakeFiles/libcopy.dir/copy.s

libcopy/CMakeFiles/libcopy.dir/copy.o.requires:

.PHONY : libcopy/CMakeFiles/libcopy.dir/copy.o.requires

libcopy/CMakeFiles/libcopy.dir/copy.o.provides: libcopy/CMakeFiles/libcopy.dir/copy.o.requires
	$(MAKE) -f libcopy/CMakeFiles/libcopy.dir/build.make libcopy/CMakeFiles/libcopy.dir/copy.o.provides.build
.PHONY : libcopy/CMakeFiles/libcopy.dir/copy.o.provides

libcopy/CMakeFiles/libcopy.dir/copy.o.provides.build: libcopy/CMakeFiles/libcopy.dir/copy.o


# Object files for target libcopy
libcopy_OBJECTS = \
"CMakeFiles/libcopy.dir/copy.o"

# External object files for target libcopy
libcopy_EXTERNAL_OBJECTS =

libcopy/liblibcopy.a: libcopy/CMakeFiles/libcopy.dir/copy.o
libcopy/liblibcopy.a: libcopy/CMakeFiles/libcopy.dir/build.make
libcopy/liblibcopy.a: libcopy/CMakeFiles/libcopy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zeng/programming/Linux-Programming/ch5/copy/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library liblibcopy.a"
	cd /home/zeng/programming/Linux-Programming/ch5/copy/build/libcopy && $(CMAKE_COMMAND) -P CMakeFiles/libcopy.dir/cmake_clean_target.cmake
	cd /home/zeng/programming/Linux-Programming/ch5/copy/build/libcopy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libcopy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libcopy/CMakeFiles/libcopy.dir/build: libcopy/liblibcopy.a

.PHONY : libcopy/CMakeFiles/libcopy.dir/build

libcopy/CMakeFiles/libcopy.dir/requires: libcopy/CMakeFiles/libcopy.dir/copy.o.requires

.PHONY : libcopy/CMakeFiles/libcopy.dir/requires

libcopy/CMakeFiles/libcopy.dir/clean:
	cd /home/zeng/programming/Linux-Programming/ch5/copy/build/libcopy && $(CMAKE_COMMAND) -P CMakeFiles/libcopy.dir/cmake_clean.cmake
.PHONY : libcopy/CMakeFiles/libcopy.dir/clean

libcopy/CMakeFiles/libcopy.dir/depend:
	cd /home/zeng/programming/Linux-Programming/ch5/copy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zeng/programming/Linux-Programming/ch5/copy /home/zeng/programming/Linux-Programming/ch5/copy/libcopy /home/zeng/programming/Linux-Programming/ch5/copy/build /home/zeng/programming/Linux-Programming/ch5/copy/build/libcopy /home/zeng/programming/Linux-Programming/ch5/copy/build/libcopy/CMakeFiles/libcopy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libcopy/CMakeFiles/libcopy.dir/depend


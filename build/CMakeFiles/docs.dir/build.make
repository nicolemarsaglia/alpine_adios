# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /autofs/nccs-svm1_sw/rhea/.swci/0-core/opt/spack/20170224/linux-rhel6-x86_64/gcc-4.4.7/cmake-3.6.1-2ihz7qgwklvemtqu7wzpdfbt3eog6sqh/bin/cmake

# The command to remove a file.
RM = /autofs/nccs-svm1_sw/rhea/.swci/0-core/opt/spack/20170224/linux-rhel6-x86_64/gcc-4.4.7/cmake-3.6.1-2ihz7qgwklvemtqu7wzpdfbt3eog6sqh/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /ccs/home/nic8504/rhea/alpine/build

# Utility rule file for docs.

# Include the progress variables for this target.
include CMakeFiles/docs.dir/progress.make

docs: CMakeFiles/docs.dir/build.make

.PHONY : docs

# Rule to build all files generated by this target.
CMakeFiles/docs.dir/build: docs

.PHONY : CMakeFiles/docs.dir/build

CMakeFiles/docs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/docs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/docs.dir/clean

CMakeFiles/docs.dir/depend:
	cd /ccs/home/nic8504/rhea/alpine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src /ccs/home/nic8504/rhea/alpine/build /ccs/home/nic8504/rhea/alpine/build /ccs/home/nic8504/rhea/alpine/build/CMakeFiles/docs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/docs.dir/depend


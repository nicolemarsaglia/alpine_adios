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

# Utility rule file for ExperimentalCoverage.

# Include the progress variables for this target.
include CMakeFiles/ExperimentalCoverage.dir/progress.make

CMakeFiles/ExperimentalCoverage:
	/autofs/nccs-svm1_sw/rhea/.swci/0-core/opt/spack/20170224/linux-rhel6-x86_64/gcc-4.4.7/cmake-3.6.1-2ihz7qgwklvemtqu7wzpdfbt3eog6sqh/bin/ctest -D ExperimentalCoverage

ExperimentalCoverage: CMakeFiles/ExperimentalCoverage
ExperimentalCoverage: CMakeFiles/ExperimentalCoverage.dir/build.make

.PHONY : ExperimentalCoverage

# Rule to build all files generated by this target.
CMakeFiles/ExperimentalCoverage.dir/build: ExperimentalCoverage

.PHONY : CMakeFiles/ExperimentalCoverage.dir/build

CMakeFiles/ExperimentalCoverage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ExperimentalCoverage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ExperimentalCoverage.dir/clean

CMakeFiles/ExperimentalCoverage.dir/depend:
	cd /ccs/home/nic8504/rhea/alpine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src /lustre/atlas/scratch/nic8504/csc094/rhea/alpine/src /ccs/home/nic8504/rhea/alpine/build /ccs/home/nic8504/rhea/alpine/build /ccs/home/nic8504/rhea/alpine/build/CMakeFiles/ExperimentalCoverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ExperimentalCoverage.dir/depend


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
CMAKE_SOURCE_DIR = /home/tpokorsk/Pulpit/DCL/DCL_Dices

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tpokorsk/Pulpit/DCL/DCL_Dices/build

# Include any dependencies generated for this target.
include src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/depend.make

# Include the progress variables for this target.
include src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/progress.make

# Include the compile flags for this target's objects.
include src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/flags.make

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o: src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/flags.make
src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o: ../src/Components/DcObjectRecognition/DcObjectRecognition.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tpokorsk/Pulpit/DCL/DCL_Dices/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o"
	cd /home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcObjectRecognition && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o -c /home/tpokorsk/Pulpit/DCL/DCL_Dices/src/Components/DcObjectRecognition/DcObjectRecognition.cpp

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.i"
	cd /home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcObjectRecognition && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tpokorsk/Pulpit/DCL/DCL_Dices/src/Components/DcObjectRecognition/DcObjectRecognition.cpp > CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.i

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.s"
	cd /home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcObjectRecognition && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tpokorsk/Pulpit/DCL/DCL_Dices/src/Components/DcObjectRecognition/DcObjectRecognition.cpp -o CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.s

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.requires:
.PHONY : src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.requires

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.provides: src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.requires
	$(MAKE) -f src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/build.make src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.provides.build
.PHONY : src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.provides

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.provides.build: src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o
.PHONY : src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.provides.build

# Object files for target DcObjectRecognition
DcObjectRecognition_OBJECTS = \
"CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o"

# External object files for target DcObjectRecognition
DcObjectRecognition_EXTERNAL_OBJECTS =

src/Components/DcObjectRecognition/libDcObjectRecognition.so: src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_gpu.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_contrib.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_legacy.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_objdetect.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_calib3d.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_features2d.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_video.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_highgui.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_ml.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_imgproc.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_flann.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: /usr/lib/libopencv_core.so.2.3.1
src/Components/DcObjectRecognition/libDcObjectRecognition.so: src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/build.make
src/Components/DcObjectRecognition/libDcObjectRecognition.so: src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libDcObjectRecognition.so"
	cd /home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcObjectRecognition && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DcObjectRecognition.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/build: src/Components/DcObjectRecognition/libDcObjectRecognition.so
.PHONY : src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/build

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/requires: src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DcObjectRecognition.cpp.o.requires
.PHONY : src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/requires

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/clean:
	cd /home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcObjectRecognition && $(CMAKE_COMMAND) -P CMakeFiles/DcObjectRecognition.dir/cmake_clean.cmake
.PHONY : src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/clean

src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/depend:
	cd /home/tpokorsk/Pulpit/DCL/DCL_Dices/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tpokorsk/Pulpit/DCL/DCL_Dices /home/tpokorsk/Pulpit/DCL/DCL_Dices/src/Components/DcObjectRecognition /home/tpokorsk/Pulpit/DCL/DCL_Dices/build /home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcObjectRecognition /home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Components/DcObjectRecognition/CMakeFiles/DcObjectRecognition.dir/depend


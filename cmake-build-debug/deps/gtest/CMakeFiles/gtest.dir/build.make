# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\MyCodeProject\CLionProjects\cpp-tools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug

# Include any dependencies generated for this target.
include deps/gtest/CMakeFiles/gtest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include deps/gtest/CMakeFiles/gtest.dir/compiler_depend.make

# Include the progress variables for this target.
include deps/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include deps/gtest/CMakeFiles/gtest.dir/flags.make

deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj: deps/gtest/CMakeFiles/gtest.dir/flags.make
deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj: deps/gtest/CMakeFiles/gtest.dir/includes_CXX.rsp
deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj: E:/MyCodeProject/CLionProjects/cpp-tools/deps/gtest/src/gtest-all.cc
deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj: deps/gtest/CMakeFiles/gtest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj"
	cd /d E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\deps\gtest && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj -MF CMakeFiles\gtest.dir\src\gtest-all.cc.obj.d -o CMakeFiles\gtest.dir\src\gtest-all.cc.obj -c E:\MyCodeProject\CLionProjects\cpp-tools\deps\gtest\src\gtest-all.cc

deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /d E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\deps\gtest && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\MyCodeProject\CLionProjects\cpp-tools\deps\gtest\src\gtest-all.cc > CMakeFiles\gtest.dir\src\gtest-all.cc.i

deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /d E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\deps\gtest && C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\MyCodeProject\CLionProjects\cpp-tools\deps\gtest\src\gtest-all.cc -o CMakeFiles\gtest.dir\src\gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.obj"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

deps/gtest/libgtest.a: deps/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj
deps/gtest/libgtest.a: deps/gtest/CMakeFiles/gtest.dir/build.make
deps/gtest/libgtest.a: deps/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest.a"
	cd /d E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\deps\gtest && $(CMAKE_COMMAND) -P CMakeFiles\gtest.dir\cmake_clean_target.cmake
	cd /d E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\deps\gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gtest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/gtest/CMakeFiles/gtest.dir/build: deps/gtest/libgtest.a
.PHONY : deps/gtest/CMakeFiles/gtest.dir/build

deps/gtest/CMakeFiles/gtest.dir/clean:
	cd /d E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\deps\gtest && $(CMAKE_COMMAND) -P CMakeFiles\gtest.dir\cmake_clean.cmake
.PHONY : deps/gtest/CMakeFiles/gtest.dir/clean

deps/gtest/CMakeFiles/gtest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\MyCodeProject\CLionProjects\cpp-tools E:\MyCodeProject\CLionProjects\cpp-tools\deps\gtest E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\deps\gtest E:\MyCodeProject\CLionProjects\cpp-tools\cmake-build-debug\deps\gtest\CMakeFiles\gtest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : deps/gtest/CMakeFiles/gtest.dir/depend


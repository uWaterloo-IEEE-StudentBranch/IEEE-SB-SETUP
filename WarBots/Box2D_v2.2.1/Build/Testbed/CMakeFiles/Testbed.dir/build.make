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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/theperv/Downloads/Box2D_v2.2.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/theperv/Downloads/Box2D_v2.2.1/Build

# Include any dependencies generated for this target.
include Testbed/CMakeFiles/Testbed.dir/depend.make

# Include the progress variables for this target.
include Testbed/CMakeFiles/Testbed.dir/progress.make

# Include the compile flags for this target's objects.
include Testbed/CMakeFiles/Testbed.dir/flags.make

Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o: Testbed/CMakeFiles/Testbed.dir/flags.make
Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o: ../Testbed/Framework/Main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/theperv/Downloads/Box2D_v2.2.1/Build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Testbed.dir/Framework/Main.cpp.o -c /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Main.cpp

Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Testbed.dir/Framework/Main.cpp.i"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Main.cpp > CMakeFiles/Testbed.dir/Framework/Main.cpp.i

Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Testbed.dir/Framework/Main.cpp.s"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Main.cpp -o CMakeFiles/Testbed.dir/Framework/Main.cpp.s

Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o.requires:
.PHONY : Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o.requires

Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o.provides: Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o.requires
	$(MAKE) -f Testbed/CMakeFiles/Testbed.dir/build.make Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o.provides.build
.PHONY : Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o.provides

Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o.provides.build: Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o

Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o: Testbed/CMakeFiles/Testbed.dir/flags.make
Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o: ../Testbed/Framework/Render.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/theperv/Downloads/Box2D_v2.2.1/Build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Testbed.dir/Framework/Render.cpp.o -c /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Render.cpp

Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Testbed.dir/Framework/Render.cpp.i"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Render.cpp > CMakeFiles/Testbed.dir/Framework/Render.cpp.i

Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Testbed.dir/Framework/Render.cpp.s"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Render.cpp -o CMakeFiles/Testbed.dir/Framework/Render.cpp.s

Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o.requires:
.PHONY : Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o.requires

Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o.provides: Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o.requires
	$(MAKE) -f Testbed/CMakeFiles/Testbed.dir/build.make Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o.provides.build
.PHONY : Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o.provides

Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o.provides.build: Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o

Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o: Testbed/CMakeFiles/Testbed.dir/flags.make
Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o: ../Testbed/Framework/Test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/theperv/Downloads/Box2D_v2.2.1/Build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Testbed.dir/Framework/Test.cpp.o -c /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Test.cpp

Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Testbed.dir/Framework/Test.cpp.i"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Test.cpp > CMakeFiles/Testbed.dir/Framework/Test.cpp.i

Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Testbed.dir/Framework/Test.cpp.s"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Framework/Test.cpp -o CMakeFiles/Testbed.dir/Framework/Test.cpp.s

Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o.requires:
.PHONY : Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o.requires

Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o.provides: Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o.requires
	$(MAKE) -f Testbed/CMakeFiles/Testbed.dir/build.make Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o.provides.build
.PHONY : Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o.provides

Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o.provides.build: Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o

Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o: Testbed/CMakeFiles/Testbed.dir/flags.make
Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o: ../Testbed/Tests/TestEntries.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/theperv/Downloads/Box2D_v2.2.1/Build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o -c /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Tests/TestEntries.cpp

Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.i"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Tests/TestEntries.cpp > CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.i

Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.s"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/theperv/Downloads/Box2D_v2.2.1/Testbed/Tests/TestEntries.cpp -o CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.s

Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o.requires:
.PHONY : Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o.requires

Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o.provides: Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o.requires
	$(MAKE) -f Testbed/CMakeFiles/Testbed.dir/build.make Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o.provides.build
.PHONY : Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o.provides

Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o.provides.build: Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o

# Object files for target Testbed
Testbed_OBJECTS = \
"CMakeFiles/Testbed.dir/Framework/Main.cpp.o" \
"CMakeFiles/Testbed.dir/Framework/Render.cpp.o" \
"CMakeFiles/Testbed.dir/Framework/Test.cpp.o" \
"CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o"

# External object files for target Testbed
Testbed_EXTERNAL_OBJECTS =

Testbed/Testbed: Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o
Testbed/Testbed: Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o
Testbed/Testbed: Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o
Testbed/Testbed: Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o
Testbed/Testbed: Box2D/libBox2D.a
Testbed/Testbed: freeglut/libfreeglut_static.a
Testbed/Testbed: glui/libglui.a
Testbed/Testbed: /usr/lib/i386-linux-gnu/libGLU.so
Testbed/Testbed: /usr/lib/i386-linux-gnu/libGL.so
Testbed/Testbed: /usr/lib/i386-linux-gnu/libSM.so
Testbed/Testbed: /usr/lib/i386-linux-gnu/libICE.so
Testbed/Testbed: /usr/lib/i386-linux-gnu/libX11.so
Testbed/Testbed: /usr/lib/i386-linux-gnu/libXext.so
Testbed/Testbed: Testbed/CMakeFiles/Testbed.dir/build.make
Testbed/Testbed: Testbed/CMakeFiles/Testbed.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Testbed"
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Testbed.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Testbed/CMakeFiles/Testbed.dir/build: Testbed/Testbed
.PHONY : Testbed/CMakeFiles/Testbed.dir/build

Testbed/CMakeFiles/Testbed.dir/requires: Testbed/CMakeFiles/Testbed.dir/Framework/Main.cpp.o.requires
Testbed/CMakeFiles/Testbed.dir/requires: Testbed/CMakeFiles/Testbed.dir/Framework/Render.cpp.o.requires
Testbed/CMakeFiles/Testbed.dir/requires: Testbed/CMakeFiles/Testbed.dir/Framework/Test.cpp.o.requires
Testbed/CMakeFiles/Testbed.dir/requires: Testbed/CMakeFiles/Testbed.dir/Tests/TestEntries.cpp.o.requires
.PHONY : Testbed/CMakeFiles/Testbed.dir/requires

Testbed/CMakeFiles/Testbed.dir/clean:
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed && $(CMAKE_COMMAND) -P CMakeFiles/Testbed.dir/cmake_clean.cmake
.PHONY : Testbed/CMakeFiles/Testbed.dir/clean

Testbed/CMakeFiles/Testbed.dir/depend:
	cd /home/theperv/Downloads/Box2D_v2.2.1/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/theperv/Downloads/Box2D_v2.2.1 /home/theperv/Downloads/Box2D_v2.2.1/Testbed /home/theperv/Downloads/Box2D_v2.2.1/Build /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed /home/theperv/Downloads/Box2D_v2.2.1/Build/Testbed/CMakeFiles/Testbed.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Testbed/CMakeFiles/Testbed.dir/depend


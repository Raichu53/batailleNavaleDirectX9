# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = "D:\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\matt0\source\repos\Raichu53\batailleNavale

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/projet.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/projet.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/projet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/projet.dir/flags.make

CMakeFiles/projet.dir/main.c.obj: CMakeFiles/projet.dir/flags.make
CMakeFiles/projet.dir/main.c.obj: ../main.c
CMakeFiles/projet.dir/main.c.obj: CMakeFiles/projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/projet.dir/main.c.obj"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/projet.dir/main.c.obj -MF CMakeFiles\projet.dir\main.c.obj.d -o CMakeFiles\projet.dir\main.c.obj -c C:\Users\matt0\source\repos\Raichu53\batailleNavale\main.c

CMakeFiles/projet.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet.dir/main.c.i"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\matt0\source\repos\Raichu53\batailleNavale\main.c > CMakeFiles\projet.dir\main.c.i

CMakeFiles/projet.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet.dir/main.c.s"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\matt0\source\repos\Raichu53\batailleNavale\main.c -o CMakeFiles\projet.dir\main.c.s

CMakeFiles/projet.dir/gamesFunctions.c.obj: CMakeFiles/projet.dir/flags.make
CMakeFiles/projet.dir/gamesFunctions.c.obj: ../gamesFunctions.c
CMakeFiles/projet.dir/gamesFunctions.c.obj: CMakeFiles/projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/projet.dir/gamesFunctions.c.obj"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/projet.dir/gamesFunctions.c.obj -MF CMakeFiles\projet.dir\gamesFunctions.c.obj.d -o CMakeFiles\projet.dir\gamesFunctions.c.obj -c C:\Users\matt0\source\repos\Raichu53\batailleNavale\gamesFunctions.c

CMakeFiles/projet.dir/gamesFunctions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet.dir/gamesFunctions.c.i"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\matt0\source\repos\Raichu53\batailleNavale\gamesFunctions.c > CMakeFiles\projet.dir\gamesFunctions.c.i

CMakeFiles/projet.dir/gamesFunctions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet.dir/gamesFunctions.c.s"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\matt0\source\repos\Raichu53\batailleNavale\gamesFunctions.c -o CMakeFiles\projet.dir\gamesFunctions.c.s

CMakeFiles/projet.dir/windowProc.c.obj: CMakeFiles/projet.dir/flags.make
CMakeFiles/projet.dir/windowProc.c.obj: ../windowProc.c
CMakeFiles/projet.dir/windowProc.c.obj: CMakeFiles/projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/projet.dir/windowProc.c.obj"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/projet.dir/windowProc.c.obj -MF CMakeFiles\projet.dir\windowProc.c.obj.d -o CMakeFiles\projet.dir\windowProc.c.obj -c C:\Users\matt0\source\repos\Raichu53\batailleNavale\windowProc.c

CMakeFiles/projet.dir/windowProc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet.dir/windowProc.c.i"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\matt0\source\repos\Raichu53\batailleNavale\windowProc.c > CMakeFiles\projet.dir\windowProc.c.i

CMakeFiles/projet.dir/windowProc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet.dir/windowProc.c.s"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\matt0\source\repos\Raichu53\batailleNavale\windowProc.c -o CMakeFiles\projet.dir\windowProc.c.s

CMakeFiles/projet.dir/dx.c.obj: CMakeFiles/projet.dir/flags.make
CMakeFiles/projet.dir/dx.c.obj: ../dx.c
CMakeFiles/projet.dir/dx.c.obj: CMakeFiles/projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/projet.dir/dx.c.obj"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/projet.dir/dx.c.obj -MF CMakeFiles\projet.dir\dx.c.obj.d -o CMakeFiles\projet.dir\dx.c.obj -c C:\Users\matt0\source\repos\Raichu53\batailleNavale\dx.c

CMakeFiles/projet.dir/dx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/projet.dir/dx.c.i"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\matt0\source\repos\Raichu53\batailleNavale\dx.c > CMakeFiles\projet.dir\dx.c.i

CMakeFiles/projet.dir/dx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/projet.dir/dx.c.s"
	"D:\CLion 2022.2.4\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\matt0\source\repos\Raichu53\batailleNavale\dx.c -o CMakeFiles\projet.dir\dx.c.s

# Object files for target projet
projet_OBJECTS = \
"CMakeFiles/projet.dir/main.c.obj" \
"CMakeFiles/projet.dir/gamesFunctions.c.obj" \
"CMakeFiles/projet.dir/windowProc.c.obj" \
"CMakeFiles/projet.dir/dx.c.obj"

# External object files for target projet
projet_EXTERNAL_OBJECTS =

projet.exe: CMakeFiles/projet.dir/main.c.obj
projet.exe: CMakeFiles/projet.dir/gamesFunctions.c.obj
projet.exe: CMakeFiles/projet.dir/windowProc.c.obj
projet.exe: CMakeFiles/projet.dir/dx.c.obj
projet.exe: CMakeFiles/projet.dir/build.make
projet.exe: ../MicrosoftDirectXSDKJune2010/Lib/x64/d3d9.lib
projet.exe: ../MicrosoftDirectXSDKJune2010/Lib/x64/d3dx9.lib
projet.exe: CMakeFiles/projet.dir/linklibs.rsp
projet.exe: CMakeFiles/projet.dir/objects1.rsp
projet.exe: CMakeFiles/projet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable projet.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\projet.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/projet.dir/build: projet.exe
.PHONY : CMakeFiles/projet.dir/build

CMakeFiles/projet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\projet.dir\cmake_clean.cmake
.PHONY : CMakeFiles/projet.dir/clean

CMakeFiles/projet.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\matt0\source\repos\Raichu53\batailleNavale C:\Users\matt0\source\repos\Raichu53\batailleNavale C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug C:\Users\matt0\source\repos\Raichu53\batailleNavale\cmake-build-debug\CMakeFiles\projet.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/projet.dir/depend

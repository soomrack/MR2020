# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "F:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "F:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Walter\CLionProjects\untitled2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Walter\CLionProjects\untitled2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\untitled2.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\untitled2.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\untitled2.dir\flags.make

CMakeFiles\untitled2.dir\main.c.obj: CMakeFiles\untitled2.dir\flags.make
CMakeFiles\untitled2.dir\main.c.obj: ..\main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Walter\CLionProjects\untitled2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/untitled2.dir/main.c.obj"
	"F:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.23.28105\bin\Hostx86\x86\cl.exe" @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\untitled2.dir\main.c.obj /FdCMakeFiles\untitled2.dir\ /FS -c C:\Users\Walter\CLionProjects\untitled2\main.c
<<

CMakeFiles\untitled2.dir\main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/untitled2.dir/main.c.i"
	"F:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.23.28105\bin\Hostx86\x86\cl.exe" > CMakeFiles\untitled2.dir\main.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Walter\CLionProjects\untitled2\main.c
<<

CMakeFiles\untitled2.dir\main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/untitled2.dir/main.c.s"
	"F:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.23.28105\bin\Hostx86\x86\cl.exe" @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\untitled2.dir\main.c.s /c C:\Users\Walter\CLionProjects\untitled2\main.c
<<

# Object files for target untitled2
untitled2_OBJECTS = \
"CMakeFiles\untitled2.dir\main.c.obj"

# External object files for target untitled2
untitled2_EXTERNAL_OBJECTS =

untitled2.exe: CMakeFiles\untitled2.dir\main.c.obj
untitled2.exe: CMakeFiles\untitled2.dir\build.make
untitled2.exe: CMakeFiles\untitled2.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Walter\CLionProjects\untitled2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable untitled2.exe"
	"F:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\untitled2.dir --rc="F:\Windows Kits\10\bin\10.0.18362.0\x86\rc.exe" --mt="F:\Windows Kits\10\bin\10.0.18362.0\x86\mt.exe" --manifests  -- "F:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.23.28105\bin\Hostx86\x86\link.exe" /nologo @CMakeFiles\untitled2.dir\objects1.rsp @<<
 /out:untitled2.exe /implib:untitled2.lib /pdb:C:\Users\Walter\CLionProjects\untitled2\cmake-build-debug\untitled2.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\untitled2.dir\build: untitled2.exe

.PHONY : CMakeFiles\untitled2.dir\build

CMakeFiles\untitled2.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\untitled2.dir\cmake_clean.cmake
.PHONY : CMakeFiles\untitled2.dir\clean

CMakeFiles\untitled2.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Walter\CLionProjects\untitled2 C:\Users\Walter\CLionProjects\untitled2 C:\Users\Walter\CLionProjects\untitled2\cmake-build-debug C:\Users\Walter\CLionProjects\untitled2\cmake-build-debug C:\Users\Walter\CLionProjects\untitled2\cmake-build-debug\CMakeFiles\untitled2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\untitled2.dir\depend


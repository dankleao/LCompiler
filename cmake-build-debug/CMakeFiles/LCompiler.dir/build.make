# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.4\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.4\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Daniel\CLionProjects\LCompiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LCompiler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LCompiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LCompiler.dir/flags.make

CMakeFiles/LCompiler.dir/lex.c.obj: CMakeFiles/LCompiler.dir/flags.make
CMakeFiles/LCompiler.dir/lex.c.obj: ../lex.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/LCompiler.dir/lex.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LCompiler.dir\lex.c.obj   -c C:\Users\Daniel\CLionProjects\LCompiler\lex.c

CMakeFiles/LCompiler.dir/lex.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCompiler.dir/lex.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Daniel\CLionProjects\LCompiler\lex.c > CMakeFiles\LCompiler.dir\lex.c.i

CMakeFiles/LCompiler.dir/lex.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCompiler.dir/lex.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Daniel\CLionProjects\LCompiler\lex.c -o CMakeFiles\LCompiler.dir\lex.c.s

CMakeFiles/LCompiler.dir/lex.c.obj.requires:

.PHONY : CMakeFiles/LCompiler.dir/lex.c.obj.requires

CMakeFiles/LCompiler.dir/lex.c.obj.provides: CMakeFiles/LCompiler.dir/lex.c.obj.requires
	$(MAKE) -f CMakeFiles\LCompiler.dir\build.make CMakeFiles/LCompiler.dir/lex.c.obj.provides.build
.PHONY : CMakeFiles/LCompiler.dir/lex.c.obj.provides

CMakeFiles/LCompiler.dir/lex.c.obj.provides.build: CMakeFiles/LCompiler.dir/lex.c.obj


CMakeFiles/LCompiler.dir/def.c.obj: CMakeFiles/LCompiler.dir/flags.make
CMakeFiles/LCompiler.dir/def.c.obj: ../def.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/LCompiler.dir/def.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LCompiler.dir\def.c.obj   -c C:\Users\Daniel\CLionProjects\LCompiler\def.c

CMakeFiles/LCompiler.dir/def.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCompiler.dir/def.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Daniel\CLionProjects\LCompiler\def.c > CMakeFiles\LCompiler.dir\def.c.i

CMakeFiles/LCompiler.dir/def.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCompiler.dir/def.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Daniel\CLionProjects\LCompiler\def.c -o CMakeFiles\LCompiler.dir\def.c.s

CMakeFiles/LCompiler.dir/def.c.obj.requires:

.PHONY : CMakeFiles/LCompiler.dir/def.c.obj.requires

CMakeFiles/LCompiler.dir/def.c.obj.provides: CMakeFiles/LCompiler.dir/def.c.obj.requires
	$(MAKE) -f CMakeFiles\LCompiler.dir\build.make CMakeFiles/LCompiler.dir/def.c.obj.provides.build
.PHONY : CMakeFiles/LCompiler.dir/def.c.obj.provides

CMakeFiles/LCompiler.dir/def.c.obj.provides.build: CMakeFiles/LCompiler.dir/def.c.obj


CMakeFiles/LCompiler.dir/error.c.obj: CMakeFiles/LCompiler.dir/flags.make
CMakeFiles/LCompiler.dir/error.c.obj: ../error.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/LCompiler.dir/error.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LCompiler.dir\error.c.obj   -c C:\Users\Daniel\CLionProjects\LCompiler\error.c

CMakeFiles/LCompiler.dir/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCompiler.dir/error.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Daniel\CLionProjects\LCompiler\error.c > CMakeFiles\LCompiler.dir\error.c.i

CMakeFiles/LCompiler.dir/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCompiler.dir/error.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Daniel\CLionProjects\LCompiler\error.c -o CMakeFiles\LCompiler.dir\error.c.s

CMakeFiles/LCompiler.dir/error.c.obj.requires:

.PHONY : CMakeFiles/LCompiler.dir/error.c.obj.requires

CMakeFiles/LCompiler.dir/error.c.obj.provides: CMakeFiles/LCompiler.dir/error.c.obj.requires
	$(MAKE) -f CMakeFiles\LCompiler.dir\build.make CMakeFiles/LCompiler.dir/error.c.obj.provides.build
.PHONY : CMakeFiles/LCompiler.dir/error.c.obj.provides

CMakeFiles/LCompiler.dir/error.c.obj.provides.build: CMakeFiles/LCompiler.dir/error.c.obj


CMakeFiles/LCompiler.dir/hash_table.c.obj: CMakeFiles/LCompiler.dir/flags.make
CMakeFiles/LCompiler.dir/hash_table.c.obj: ../hash_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/LCompiler.dir/hash_table.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LCompiler.dir\hash_table.c.obj   -c C:\Users\Daniel\CLionProjects\LCompiler\hash_table.c

CMakeFiles/LCompiler.dir/hash_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCompiler.dir/hash_table.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Daniel\CLionProjects\LCompiler\hash_table.c > CMakeFiles\LCompiler.dir\hash_table.c.i

CMakeFiles/LCompiler.dir/hash_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCompiler.dir/hash_table.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Daniel\CLionProjects\LCompiler\hash_table.c -o CMakeFiles\LCompiler.dir\hash_table.c.s

CMakeFiles/LCompiler.dir/hash_table.c.obj.requires:

.PHONY : CMakeFiles/LCompiler.dir/hash_table.c.obj.requires

CMakeFiles/LCompiler.dir/hash_table.c.obj.provides: CMakeFiles/LCompiler.dir/hash_table.c.obj.requires
	$(MAKE) -f CMakeFiles\LCompiler.dir\build.make CMakeFiles/LCompiler.dir/hash_table.c.obj.provides.build
.PHONY : CMakeFiles/LCompiler.dir/hash_table.c.obj.provides

CMakeFiles/LCompiler.dir/hash_table.c.obj.provides.build: CMakeFiles/LCompiler.dir/hash_table.c.obj


CMakeFiles/LCompiler.dir/symbol_table.c.obj: CMakeFiles/LCompiler.dir/flags.make
CMakeFiles/LCompiler.dir/symbol_table.c.obj: ../symbol_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/LCompiler.dir/symbol_table.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LCompiler.dir\symbol_table.c.obj   -c C:\Users\Daniel\CLionProjects\LCompiler\symbol_table.c

CMakeFiles/LCompiler.dir/symbol_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCompiler.dir/symbol_table.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Daniel\CLionProjects\LCompiler\symbol_table.c > CMakeFiles\LCompiler.dir\symbol_table.c.i

CMakeFiles/LCompiler.dir/symbol_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCompiler.dir/symbol_table.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Daniel\CLionProjects\LCompiler\symbol_table.c -o CMakeFiles\LCompiler.dir\symbol_table.c.s

CMakeFiles/LCompiler.dir/symbol_table.c.obj.requires:

.PHONY : CMakeFiles/LCompiler.dir/symbol_table.c.obj.requires

CMakeFiles/LCompiler.dir/symbol_table.c.obj.provides: CMakeFiles/LCompiler.dir/symbol_table.c.obj.requires
	$(MAKE) -f CMakeFiles\LCompiler.dir\build.make CMakeFiles/LCompiler.dir/symbol_table.c.obj.provides.build
.PHONY : CMakeFiles/LCompiler.dir/symbol_table.c.obj.provides

CMakeFiles/LCompiler.dir/symbol_table.c.obj.provides.build: CMakeFiles/LCompiler.dir/symbol_table.c.obj


CMakeFiles/LCompiler.dir/parser.c.obj: CMakeFiles/LCompiler.dir/flags.make
CMakeFiles/LCompiler.dir/parser.c.obj: ../parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/LCompiler.dir/parser.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LCompiler.dir\parser.c.obj   -c C:\Users\Daniel\CLionProjects\LCompiler\parser.c

CMakeFiles/LCompiler.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCompiler.dir/parser.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Daniel\CLionProjects\LCompiler\parser.c > CMakeFiles\LCompiler.dir\parser.c.i

CMakeFiles/LCompiler.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCompiler.dir/parser.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Daniel\CLionProjects\LCompiler\parser.c -o CMakeFiles\LCompiler.dir\parser.c.s

CMakeFiles/LCompiler.dir/parser.c.obj.requires:

.PHONY : CMakeFiles/LCompiler.dir/parser.c.obj.requires

CMakeFiles/LCompiler.dir/parser.c.obj.provides: CMakeFiles/LCompiler.dir/parser.c.obj.requires
	$(MAKE) -f CMakeFiles\LCompiler.dir\build.make CMakeFiles/LCompiler.dir/parser.c.obj.provides.build
.PHONY : CMakeFiles/LCompiler.dir/parser.c.obj.provides

CMakeFiles/LCompiler.dir/parser.c.obj.provides.build: CMakeFiles/LCompiler.dir/parser.c.obj


CMakeFiles/LCompiler.dir/translator.c.obj: CMakeFiles/LCompiler.dir/flags.make
CMakeFiles/LCompiler.dir/translator.c.obj: ../translator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/LCompiler.dir/translator.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\LCompiler.dir\translator.c.obj   -c C:\Users\Daniel\CLionProjects\LCompiler\translator.c

CMakeFiles/LCompiler.dir/translator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LCompiler.dir/translator.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Daniel\CLionProjects\LCompiler\translator.c > CMakeFiles\LCompiler.dir\translator.c.i

CMakeFiles/LCompiler.dir/translator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LCompiler.dir/translator.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Daniel\CLionProjects\LCompiler\translator.c -o CMakeFiles\LCompiler.dir\translator.c.s

CMakeFiles/LCompiler.dir/translator.c.obj.requires:

.PHONY : CMakeFiles/LCompiler.dir/translator.c.obj.requires

CMakeFiles/LCompiler.dir/translator.c.obj.provides: CMakeFiles/LCompiler.dir/translator.c.obj.requires
	$(MAKE) -f CMakeFiles\LCompiler.dir\build.make CMakeFiles/LCompiler.dir/translator.c.obj.provides.build
.PHONY : CMakeFiles/LCompiler.dir/translator.c.obj.provides

CMakeFiles/LCompiler.dir/translator.c.obj.provides.build: CMakeFiles/LCompiler.dir/translator.c.obj


# Object files for target LCompiler
LCompiler_OBJECTS = \
"CMakeFiles/LCompiler.dir/lex.c.obj" \
"CMakeFiles/LCompiler.dir/def.c.obj" \
"CMakeFiles/LCompiler.dir/error.c.obj" \
"CMakeFiles/LCompiler.dir/hash_table.c.obj" \
"CMakeFiles/LCompiler.dir/symbol_table.c.obj" \
"CMakeFiles/LCompiler.dir/parser.c.obj" \
"CMakeFiles/LCompiler.dir/translator.c.obj"

# External object files for target LCompiler
LCompiler_EXTERNAL_OBJECTS =

LCompiler.exe: CMakeFiles/LCompiler.dir/lex.c.obj
LCompiler.exe: CMakeFiles/LCompiler.dir/def.c.obj
LCompiler.exe: CMakeFiles/LCompiler.dir/error.c.obj
LCompiler.exe: CMakeFiles/LCompiler.dir/hash_table.c.obj
LCompiler.exe: CMakeFiles/LCompiler.dir/symbol_table.c.obj
LCompiler.exe: CMakeFiles/LCompiler.dir/parser.c.obj
LCompiler.exe: CMakeFiles/LCompiler.dir/translator.c.obj
LCompiler.exe: CMakeFiles/LCompiler.dir/build.make
LCompiler.exe: CMakeFiles/LCompiler.dir/linklibs.rsp
LCompiler.exe: CMakeFiles/LCompiler.dir/objects1.rsp
LCompiler.exe: CMakeFiles/LCompiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable LCompiler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LCompiler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LCompiler.dir/build: LCompiler.exe

.PHONY : CMakeFiles/LCompiler.dir/build

CMakeFiles/LCompiler.dir/requires: CMakeFiles/LCompiler.dir/lex.c.obj.requires
CMakeFiles/LCompiler.dir/requires: CMakeFiles/LCompiler.dir/def.c.obj.requires
CMakeFiles/LCompiler.dir/requires: CMakeFiles/LCompiler.dir/error.c.obj.requires
CMakeFiles/LCompiler.dir/requires: CMakeFiles/LCompiler.dir/hash_table.c.obj.requires
CMakeFiles/LCompiler.dir/requires: CMakeFiles/LCompiler.dir/symbol_table.c.obj.requires
CMakeFiles/LCompiler.dir/requires: CMakeFiles/LCompiler.dir/parser.c.obj.requires
CMakeFiles/LCompiler.dir/requires: CMakeFiles/LCompiler.dir/translator.c.obj.requires

.PHONY : CMakeFiles/LCompiler.dir/requires

CMakeFiles/LCompiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LCompiler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LCompiler.dir/clean

CMakeFiles/LCompiler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Daniel\CLionProjects\LCompiler C:\Users\Daniel\CLionProjects\LCompiler C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug C:\Users\Daniel\CLionProjects\LCompiler\cmake-build-debug\CMakeFiles\LCompiler.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LCompiler.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.21.3_1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.21.3_1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08"

# Include any dependencies generated for this target.
include CMakeFiles/d_08.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/d_08.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/d_08.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/d_08.dir/flags.make

CMakeFiles/d_08.dir/d_08.cpp.o: CMakeFiles/d_08.dir/flags.make
CMakeFiles/d_08.dir/d_08.cpp.o: d_08.cpp
CMakeFiles/d_08.dir/d_08.cpp.o: CMakeFiles/d_08.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/d_08.dir/d_08.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/d_08.dir/d_08.cpp.o -MF CMakeFiles/d_08.dir/d_08.cpp.o.d -o CMakeFiles/d_08.dir/d_08.cpp.o -c "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08/d_08.cpp"

CMakeFiles/d_08.dir/d_08.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/d_08.dir/d_08.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08/d_08.cpp" > CMakeFiles/d_08.dir/d_08.cpp.i

CMakeFiles/d_08.dir/d_08.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/d_08.dir/d_08.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08/d_08.cpp" -o CMakeFiles/d_08.dir/d_08.cpp.s

# Object files for target d_08
d_08_OBJECTS = \
"CMakeFiles/d_08.dir/d_08.cpp.o"

# External object files for target d_08
d_08_EXTERNAL_OBJECTS =

d_08: CMakeFiles/d_08.dir/d_08.cpp.o
d_08: CMakeFiles/d_08.dir/build.make
d_08: /opt/homebrew/lib/libsndfile.dylib
d_08: CMakeFiles/d_08.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable d_08"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/d_08.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/d_08.dir/build: d_08
.PHONY : CMakeFiles/d_08.dir/build

CMakeFiles/d_08.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/d_08.dir/cmake_clean.cmake
.PHONY : CMakeFiles/d_08.dir/clean

CMakeFiles/d_08.dir/depend:
	cd "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08" "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08" "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08" "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08" "/Users/joaovieira/OneDrive - Universidade de Aveiro/Universidade/Universidade/4º ano/1 semestre/informacao_codificacao/git/Informacao_codificacao/d08/CMakeFiles/d_08.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/d_08.dir/depend


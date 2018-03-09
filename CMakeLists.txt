cmake_minimum_required(VERSION 3.7)
project(CompilerL)

set(CMAKE_C_STANDARD 99)

<<<<<<< HEAD
set(SOURCE_FILES def.h lex.h hash_table.c hash_table.h def.c tblerrors.h)
=======
set(SOURCE_FILES def.h lex.h hash_table.c hash_table.h main.c def.c tblerrors.h)
>>>>>>> master
add_executable(CompilerL ${SOURCE_FILES})
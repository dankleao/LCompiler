cmake_minimum_required(VERSION 3.9)
project(LCompiler C)

set(CMAKE_C_STANDARD 99)

add_executable(LCompiler hash_table.c hash_table.h def.c def.h config.h error.c error.h lex.c lex.h symbol_table.c symbol_table.h parser.c parser.h)
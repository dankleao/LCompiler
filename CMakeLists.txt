cmake_minimum_required(VERSION 3.7.2)
project(LCompiler C)

set(CMAKE_C_STANDARD 99)

add_executable(LCompiler lex.c lex.h def.c def.h config.h error.c error.h hash_table.c hash_table.h symbol_table.c symbol_table.h parser.c parser.h code_generator.c code_generator.h)
cmake_minimum_required(VERSION 3.20)

project(svm C)

set(CMAKE_C_COMPILER "cc")
set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99 -pedantic")

add_executable(svm ./src/inst.c ./src/inst.h ./src/svm.c ./src/svm.h ./src/parser.c ./src/parser.h ./src/main.c)
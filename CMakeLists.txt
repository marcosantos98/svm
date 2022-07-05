cmake_minimum_required(VERSION 3.20)

project(svm C)

set(CMAKE_C_COMPILER "cc")
set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99 -pedantic")

add_executable(svm inst.c inst.h svm.c svm.h parser.c parser.h main.c)
cmake_minimum_required(VERSION 3.21)
project(projekt C)

set(CMAKE_C_STANDARD 11)

add_executable(projekt main.c)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
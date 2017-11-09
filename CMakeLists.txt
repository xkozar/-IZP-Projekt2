cmake_minimum_required(VERSION 3.8)
project(proj2)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Werror")
set(SOURCE_FILES main.c)
add_executable(proj2 ${SOURCE_FILES})
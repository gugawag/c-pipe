cmake_minimum_required(VERSION 3.3)
project(c_pipe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES unix_pipe.c)
add_executable(c_pipe ${SOURCE_FILES})
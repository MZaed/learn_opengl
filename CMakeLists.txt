cmake_minimum_required(VERSION 3.10)
project(learn_opengl VERSION 0.0.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 14)

message(STATUS "Processing Main CMakeLists")
#include external source code and libraries
add_subdirectory(external)
add_subdirectory(opengl)
add_subdirectory(main_program)




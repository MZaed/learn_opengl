cmake_minimum_required(VERSION 3.16)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external)
add_subdirectory(main_program)

set_target_properties(learn_opengl
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )


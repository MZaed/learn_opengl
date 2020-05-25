add_library(
        glad_lib
        STATIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
)

set_target_properties(
        glad_lib
        PROPERTIES LINKER_LANGUAGE CXX
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(
        glad_lib
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

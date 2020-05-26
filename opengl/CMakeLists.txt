add_library(
        opengl_wrapper_lib
        STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_include_directories(
        opengl_wrapper_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        opengl_wrapper_lib
        glad_lib
)

set_target_properties(
        opengl_wrapper_lib
        PROPERTIES LINKER_LANGUAGE CXX
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

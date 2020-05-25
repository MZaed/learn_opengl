add_library(glfw3_lib STATIC  " ")

set_target_properties(
        glfw3_lib
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


set_target_properties(
        glfw3_lib
        PROPERTIES LINKER_LANGUAGE CXX
)

target_include_directories(
        glfw3_lib
        PUBLIC
        "${CMAKE_SOURCE_DIR}/external"
)

target_link_libraries(
        glfw3_lib
        "${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll"
)

add_custom_command(
        TARGET  glfw3_lib
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll"
        "${CMAKE_BINARY_DIR}/bin/"
        COMMENT "Copying  shared library glfw3.dll to bin folder"
)

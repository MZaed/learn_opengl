add_library(glfw3_lib SHARED  " ")

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
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw3.dll
)

target_include_directories(
        glfw3_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        glfw3_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw3.dll
)

add_custom_command(
    TARGET  glfw3_lib
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw3.dll"
    "${CMAKE_BINARY_DIR}/bin/"
     COMMENT "Copying  shared library glfw3"
)

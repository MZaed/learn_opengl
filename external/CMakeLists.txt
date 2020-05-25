add_library(external_target SHARED " ")


set_target_properties(
        external_target
        PROPERTIES LINKER_LANGUAGE CXX
)

set_target_properties(external_target
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_library(glfw3 SHARED IMPORTED)

set_target_properties(
        glfw3
        PROPERTIES LINKER_LANGUAGE CXX
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw3.dll
)

target_link_libraries(
        external_target
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw3.dll
)

target_include_directories(
        external_target
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_custom_command(
    TARGET external_target POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw3.dll"
    "${CMAKE_BINARY_DIR}/bin/"
     COMMENT "Copying  shared library glfw3"
)

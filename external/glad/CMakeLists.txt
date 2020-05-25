add_library(
        glad_lib
        STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/
        ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
        glad_lib
        PROPERTIES LINKER_LANGUAGE CXX
)

target_include_directories(
        glad_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
        glad_lib

)

set_target_properties(
        glad_lib
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

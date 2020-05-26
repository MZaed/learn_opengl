message(STATUS "Processing GLFW")

add_library(glfw STATIC IMPORTED)

set_target_properties(
        glfw
        PROPERTIES
        IMPORTED_GLOBAL TRUE
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/libglfw3.a"
)

target_include_directories(
        glfw BEFORE
        INTERFACE "${CMAKE_SOURCE_DIR}/external"
)



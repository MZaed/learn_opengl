message(STATUS "Processing glad")
add_library(glad)

target_sources(
        glad
        PRIVATE "src/glad.c"
)

target_include_directories(
        glad BEFORE
        PUBLIC "${CMAKE_SOURCE_DIR}/external/glad/include"
)

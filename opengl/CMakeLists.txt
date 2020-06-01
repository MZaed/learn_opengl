message(STATUS "Processing Opengl")

add_library(opengl)


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(IS_GNU=1)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(IS_MSVC=1)
endif()

target_sources(
        opengl
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/gl_error_check.cpp
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/shader.cpp
)

target_include_directories(
        opengl
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc"
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/res"
)

target_link_libraries(
        opengl
        PRIVATE glfw
        PRIVATE glad

)

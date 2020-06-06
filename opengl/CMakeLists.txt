message(STATUS "Processing Opengl")

add_library(opengl)

if (${GNU})
    target_compile_definitions(opengl PUBLIC IS_GNU=1)
elseif(${MSVC})
    target_compile_definitions(opengl PUBLIC IS_MSVC=1)
else()
    message(FATAL_ERROR "Compiler not defined")
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

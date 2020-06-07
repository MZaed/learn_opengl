
message(STATUS "Processing main_program")

add_executable(main main.cpp)

target_link_libraries(
        main
        PRIVATE glfw
        PRIVATE glad
        PRIVATE stb_image
        PRIVATE opengl
)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/opengl/res/ ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Copying Res Directory to main_program binary directory"
)


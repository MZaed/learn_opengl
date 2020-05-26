
message(STATUS "Processing main_program")

link_directories("${CMAKE_SOURCE_DIR}/external/GLFW")

add_executable(main main.cpp)

target_link_libraries(
        main
        PRIVATE glfw
        PRIVATE glad
)



#Create a executable target
add_executable(learn_opengl main.cpp)

set_target_properties( learn_opengl
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

#link the libraries
target_link_libraries(
        learn_opengl
        PRIVATE
        glfw3_lib
        glad_lib
)

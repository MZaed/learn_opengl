message(STATUS "Processing External Library")

#include GLFW Precompiled library
add_subdirectory(GLFW)
#include glad precompiled library
add_subdirectory(glad)
#include stb precompiled library
add_subdirectory(stb_image)

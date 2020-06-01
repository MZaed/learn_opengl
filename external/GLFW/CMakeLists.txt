message(STATUS "Processing GLFW")

add_library(glfw STATIC IMPORTED)

set(GLFW_STATIC_LIB_PATH "")

#Link the proper library as per the target
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(GLFW_STATIC_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib_gnu/libglfw3.a")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(GLFW_STATIC_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib_vc2019/glfw3.lib")
    add_compile_definitions(IS_MSVC=1)
endif()

#set_target_properties(glfw PROPERTIES COMPILE_DEFINITIONS BUILDER_STATIC_DEFINE)

message(STATUS "GLFW Lib path: ${GLFW_STATIC_LIB_PATH}")
set_target_properties(
        glfw
        PROPERTIES
        IMPORTED_GLOBAL TRUE
        IMPORTED_LOCATION ${GLFW_STATIC_LIB_PATH}
)

target_include_directories(
        glfw BEFORE
        INTERFACE "${CMAKE_SOURCE_DIR}/external"
)



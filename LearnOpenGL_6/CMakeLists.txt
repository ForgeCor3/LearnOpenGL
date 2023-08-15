cmake_minimum_required(VERSION 3.27.0)

project(LearnOpenGL_6)

include_directories(
    include
    include/glad
    include/GLFW
    include/KHR
    )

link_directories(lib)

add_executable(LearnOpenGL_6
    src/glad.c
    src/Shader.cpp
    src/main.cpp
    )

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/shaders
    ${PROJECT_BINARY_DIR}/shaders
    COMMENT "Copying shaders into binary directory"
    )

add_dependencies(LearnOpenGL_6 copy_shaders)

target_link_libraries(LearnOpenGL_6 glfw3)
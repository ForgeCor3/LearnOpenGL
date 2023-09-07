cmake_minimum_required(VERSION 3.27.0)

project(LearnOpenGL_Exercises_6.8.3)

include_directories(
    ../../LearnOpenGL_Include/
    ../../LearnOpenGL_Include/glad
    ../../LearnOpenGL_Include/GLFW
    ../../LearnOpenGL_Include/KHR
    )

link_directories(../../LearnOpenGL_Lib/)

add_executable(LearnOpenGL_Exercises_6.8.3
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

add_dependencies(LearnOpenGL_Exercises_6.8.3 copy_shaders)

target_link_libraries(LearnOpenGL_Exercises_6.8.3 glfw3)
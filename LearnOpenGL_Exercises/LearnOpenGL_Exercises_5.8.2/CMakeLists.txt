cmake_minimum_required(VERSION 3.27.0)

project(LearnOpenGL_Exercises_5.8.2)

include_directories(
    include
    include/glad
    include/GLFW
    include/KHR
    )

link_directories(lib)

add_executable(LearnOpenGL_Exercises_5.8.2
    src/glad.c
    src/main.cpp
    )

target_link_libraries(LearnOpenGL_Exercises_5.8.2 glfw3)
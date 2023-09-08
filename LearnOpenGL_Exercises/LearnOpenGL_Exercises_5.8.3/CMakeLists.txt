cmake_minimum_required(VERSION 3.27.0)

project(LearnOpenGL_Exercises_5.8.3)

include_directories(
    ../../LearnOpenGL_Include/
    ../../LearnOpenGL_Include/glad
    ../../LearnOpenGL_Include/GLFW
    ../../LearnOpenGL_Include/KHR
    )

link_directories(../../LearnOpenGL_Lib/)

add_executable(LearnOpenGL_Exercises_5.8.3
    ../LearnOpenGL_Executable/glad.c
    main.cpp
    )

target_link_libraries(LearnOpenGL_Exercises_5.8.3 glfw3)
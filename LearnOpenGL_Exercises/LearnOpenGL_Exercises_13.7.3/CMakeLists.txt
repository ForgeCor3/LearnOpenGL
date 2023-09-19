cmake_minimum_required(VERSION 3.27.0)

project(LearnOpenGL_Exercises_13.7.3)

include_directories(
    ../../LearnOpenGL_Include/
    ../../LearnOpenGL_Include/glad
    ../../LearnOpenGL_Include/GLFW
    ../../LearnOpenGL_Include/glm
    ../../LearnOpenGL_Include/KHR
    )

link_directories(../../LearnOpenGL_Lib/)

add_executable(LearnOpenGL_Exercises_13.7.3
    ../../LearnOpenGL_Executable/glad.c
    ../../LearnOpenGL_Executable/stb_image.cpp
    ../../LearnOpenGL_Executable/Shader.cpp
    ../../LearnOpenGL_Executable/Camera.cpp
    main.cpp
    )

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/shaders
    ${PROJECT_BINARY_DIR}/shaders
    COMMENT "Copying shaders into binary directory"
    )
add_dependencies(LearnOpenGL_Exercises_13.7.3 copy_shaders)

target_link_libraries(LearnOpenGL_Exercises_13.7.3 glfw3)
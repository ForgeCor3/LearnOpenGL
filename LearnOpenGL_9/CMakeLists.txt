cmake_minimum_required(VERSION 3.27.0)

project(LearnOpenGL_9)

include_directories(
    include
    include/glad
    include/GLFW
    include/glm
    include/KHR
    )

link_directories(lib)

add_executable(LearnOpenGL_9
    src/glad.c
    src/stb_image.cpp
    src/Shader.cpp
    src/main.cpp
    )

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/shaders
    ${PROJECT_BINARY_DIR}/shaders
    COMMENT "Copying shaders into binary directory"
    )
add_dependencies(LearnOpenGL_9 copy_shaders)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    ${PROJECT_BINARY_DIR}/resources
    COMMENT "Copying resources into binary directory"
    )
add_dependencies(LearnOpenGL_9 copy_resources)

target_link_libraries(LearnOpenGL_9 glfw3)
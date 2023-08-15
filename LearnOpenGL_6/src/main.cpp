#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>

const int width = 800;
const int height = 600;

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL_6", NULL, NULL);
    if(window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD";
        return -1;
    }
    glViewport(0, 0, width, height);

    int success;
    char infoLog[512];

    Shader vertexShader("../shaders/vertex/vertexShaderSource.vert", GL_VERTEX_SHADER);
    Shader fragmentShader("../shaders/fragment/fragmentShaderSource.frag", GL_FRAGMENT_SHADER);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    vertexShader.attachShader(shaderProgram);
    fragmentShader.attachShader(shaderProgram);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "[ERROR] PROGRAM::SHADER::COMPILATION_FAILED: " << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    vertexShader.deleteShader();
    fragmentShader.deleteShader();

    float triangle[] = 
    {   //Positions      //Colors
        -0.5, -0.5, 0.0, 1.0f, 0.0f, 0.0f,
         0.5, -0.5, 0.0, 0.0f, 1.0f, 0.0f,
         0.0,  0.5, 0.0, 0.0f, 0.0f, 1.0f
    };

    unsigned int VBO;
    unsigned int VAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

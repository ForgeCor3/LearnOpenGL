#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

#include <iostream>
#include <string>
#include <fstream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Camera camera;

float lastX = SCREEN_WIDTH / 2;
float lastY = SCREEN_HEIGHT / 2;

bool firstMouseInput = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
    float FxPos = static_cast<float>(xPos);
    float FyPos = static_cast<float>(yPos);

    if(firstMouseInput)
    {
        lastX = FxPos;
        lastY = FyPos;
        firstMouseInput = false;
    }

    float xOffset = FxPos - lastX;
    float yOffset = lastY - FyPos;

    lastX = FxPos;
    lastY = FyPos;

    camera.processMouseInput(xOffset, yOffset);
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    camera.processMouseScroll(static_cast<float>(yOffset));
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL_Exercises", NULL, NULL);
    if(window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD";
        return -1;
    }
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    int success;
    char infoLog[512];

    unsigned int objectShaderProgram;
    unsigned int lightSourceShaderProgram;
    objectShaderProgram = glCreateProgram();
    lightSourceShaderProgram = glCreateProgram();

    Shader objectVertexShader("../shaders/vertex/objectShader.vert", GL_VERTEX_SHADER);
    Shader objectFragmentShader("../shaders/fragment/objectShader.frag", GL_FRAGMENT_SHADER);
    Shader lightSourceVertexShader("../shaders/vertex/lightSourceShader.vert", GL_VERTEX_SHADER);
    Shader lightSourceFragmentShader("../shaders/fragment/lightSourceShader.frag", GL_FRAGMENT_SHADER);

    objectVertexShader.attachShader(objectShaderProgram);
    objectFragmentShader.attachShader(objectShaderProgram);
    lightSourceVertexShader.attachShader(lightSourceShaderProgram);
    lightSourceFragmentShader.attachShader(lightSourceShaderProgram);
    
    glLinkProgram(objectShaderProgram);
    glGetProgramiv(objectShaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(objectShaderProgram, 512, NULL, infoLog);
        std::cerr << "[ERROR] PROGRAM::SHADER::OBJECT::COMPILATION_FAILED: " << infoLog << std::endl;
    }

    glLinkProgram(lightSourceShaderProgram);
    glGetProgramiv(lightSourceShaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(lightSourceShaderProgram, 512, NULL, infoLog);
        std::cerr << "[ERROR] PROGRAM::SHADER::LIGHTSOURCE::COMPILATION_FAILED: " << infoLog << std::endl;
    }
    
    objectVertexShader.deleteShader();
    objectFragmentShader.deleteShader();
    lightSourceVertexShader.deleteShader();
    lightSourceFragmentShader.deleteShader();

    float cube[] = 
    {
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,    -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f
    };

    unsigned int VBO;
    unsigned int ObjectVAO;
    unsigned int LightVAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &ObjectVAO);
    glGenVertexArrays(1, &LightVAO);
    
    glBindVertexArray(ObjectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(LightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::vec3 lightSourcePosition(2.0f * cos(glfwGetTime()), 1.5f, 2.0f * sin(glfwGetTime()));

        processInput(window);

        glUseProgram(objectShaderProgram);
        glUniform3f(glGetUniformLocation(objectShaderProgram, "lightColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(objectShaderProgram, "objectColor"), 1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(objectShaderProgram, "lightPosition"), lightSourcePosition.x, lightSourcePosition.y, lightSourcePosition.z);
        glUniform3f(glGetUniformLocation(objectShaderProgram, "viewPosition"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getLookAt();
        glm::mat4 model = glm::mat4(1.0f);

        glUniformMatrix4fv(glGetUniformLocation(objectShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(objectShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(objectShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(ObjectVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glUseProgram(lightSourceShaderProgram);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightSourcePosition);
        model = glm::scale(model, glm::vec3(0.2f));

        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(LightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &ObjectVAO);
    glDeleteVertexArrays(1, &LightVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
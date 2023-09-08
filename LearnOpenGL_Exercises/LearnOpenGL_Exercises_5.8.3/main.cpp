#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const char* vertexShaderSource = 
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

const char* redFragmentShaderSource =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "}\0";

const char* yellowFragmentShaderSource =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
            "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL_Exercises", NULL, NULL);
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
    glViewport(0, 0, 800, 600);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "[ERROR] SHADER::VERTEX::COMPILATION_FAILED: " << infoLog << std::endl;
    }

    unsigned int redFragmentShader;
    redFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(redFragmentShader, 1, &redFragmentShaderSource, NULL);
    glCompileShader(redFragmentShader);
    glGetShaderiv(redFragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(redFragmentShader, 512, NULL, infoLog);
        std::cerr << "[ERROR] SHADER::FRAGMENT::COMPILATION_FAILED: " << infoLog << std::endl;
    }

    unsigned int yellowFragmentShader;
    yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
    glCompileShader(yellowFragmentShader);
    glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(yellowFragmentShader, 512, NULL, infoLog);
        std::cerr << "[ERROR] SHADER::FRAGMENT::COMPILATION_FAILED: " << infoLog << std::endl;
    }

    unsigned int redShaderProgram;
    redShaderProgram = glCreateProgram();
    glAttachShader(redShaderProgram, vertexShader);
    glAttachShader(redShaderProgram, redFragmentShader);
    glLinkProgram(redShaderProgram);
    glGetProgramiv(redShaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(redShaderProgram, 512, NULL, infoLog);
        std::cerr << "[ERROR] SHADER::FRAGMENT::COMPILATION_FAILED: " << infoLog << std::endl;
    }

    unsigned int yellowShaderProgram;
    yellowShaderProgram = glCreateProgram();
    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, yellowFragmentShader);
    glLinkProgram(yellowShaderProgram);
    glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(yellowShaderProgram, 512, NULL, infoLog);
        std::cerr << "[ERROR] SHADER::FRAGMENT::COMPILATION_FAILED: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(redFragmentShader);
    glDeleteShader(yellowFragmentShader);

    float triangle1[] = 
    {
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
         0.0f, 0.0f, 0.0f
    };

    float triangle2[] =
    {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    unsigned int VBO1;
    unsigned int VAO1;
    unsigned int VBO2;
    unsigned int VAO2;

    glGenBuffers(1, &VBO1);
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO2);
    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(redShaderProgram);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
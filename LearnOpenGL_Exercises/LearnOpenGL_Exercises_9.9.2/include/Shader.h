#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>

class Shader
{
public:
    Shader(std::string shaderFilePath, GLenum type);
    ~Shader() {};

    void attachShader(unsigned int shaderProgram);
    void deleteShader();
private:
    std::string readFile(std::string shaderFilePath);

    unsigned int ID;

    int success;
    char infoLog[512];
};
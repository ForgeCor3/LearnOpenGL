#include "Shader.h"

Shader::Shader(std::string shaderFilePath, GLenum type)
{
    //GL_FRAGMENT_SHADER = 0x8B30   GL_VERTEX_SHADER = 0x8B31
    if(type != 0x8B30 && type != 0x8B31)
        std::cerr << "Unable to create shader. Wrong shader type." << std::endl;

    ID = glCreateShader(type);

    std::string shaderSourceStr = readFile(shaderFilePath);
    const char* shaderSource = shaderSourceStr.c_str();
    glShaderSource(ID, 1, &shaderSource, NULL);

    glCompileShader(ID);
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "[ERROR] SHADER::COMPILATION_FAILED: " << infoLog << std::endl;
    }
}

void Shader::attachShader(unsigned int shaderProgram)
{
    glAttachShader(shaderProgram, ID);
}

void Shader::deleteShader()
{
    glDeleteShader(ID);
}

std::string Shader::readFile(std::string shaderFilePath)
{
    std::fstream fs;
    fs.open(shaderFilePath, std::fstream::in);
    if(fs.is_open())
    {
        std::string content;
        std::string line;

        while(std::getline(fs, line))
        {
            content.append(line + "\n");
        }
        content.append("\0");
        return content;
    }

    std::cerr << "Could not open file: " << shaderFilePath << ". File does not exist." << std::endl;
    return "";
}
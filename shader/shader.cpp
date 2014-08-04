
#include "shader.h"

#include <iostream>
#include <fstream>
#include <string.h>


Shader::Shader()
{
    m_Program = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(m_Program);
}

GLuint Shader::GetProgram()
{
    return m_Program;
}

bool Shader::AddShader(GLenum type, const std::string &path)
{
    GLuint shader;
    std::ifstream file(path, std::ios_base::in);

    if (!file)
    {
        return false;
    }

    file.seekg(0, std::ios_base::end);

    int size = file.tellg();

    file.seekg(0, std::ios_base::beg);

    GLchar *buffer = new char[size + 1];
    memset(buffer, 0, size + 1);

    file.read(buffer, size);

    std::cerr << buffer << std::endl;

    if (!file)
    {
        delete [] buffer;
    }

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&buffer, 0);
    glCompileShader(shader);

    delete [] buffer;
    file.close();


    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, (GLint*)&size);
    if (size > 0)
    {
        buffer = new char[size];
        glGetShaderInfoLog(shader, size, (GLint*)&size, buffer);

        std::cerr << "Shader compile log:" << std::endl << buffer << std::endl;

        delete [] buffer;
    }

    GLint status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        std::cerr << "Shader status is: " << status << std::endl;
        glDeleteShader(shader);

        return false;
    }

    glAttachShader(m_Program, shader);

    return true;
}

bool Shader::LinkProgram()
{
    glLinkProgram(m_Program);

    int size = 0;

    glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &size);
    if (size > 0)
    {
        char *buffer = new char[size];

        glGetProgramInfoLog(m_Program, size, &size, buffer);

        std::cerr << "Program link log: " << std::endl << buffer << std::endl;

        delete [] buffer;
    }

    GLint status;

    glGetProgramiv(m_Program, GL_LINK_STATUS, &status);
    if (status == 0)
    {
        glDeleteProgram(m_Program);

        return false;
    }

    return true;
}

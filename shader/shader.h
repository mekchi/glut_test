#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>


#define ATTR_VERTEX 3



class Shader
{
public:
    Shader();
    ~Shader();

    bool AddShader(GLenum type, const std::string &path);
    bool LinkProgram();



    GLuint GetProgram();

private:



    GLuint m_Program;
};


#endif

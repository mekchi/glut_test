
#include <iostream>

#include <memory>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <IL/il.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "work_test/arc.h"
#include "shader/shader.h"


glm::mat4 g_Modelview, g_FBModelview;
glm::mat4 g_Projection, g_FBProjection;

GLuint g_FBTexture, g_FB;
ILuint g_ILTexture;

GLuint modelview, projection, color;

GLuint g_VAO, g_VBO;

std::unique_ptr<MekArc2D> g_Arc;
std::unique_ptr<Shader> g_Shader;


void reshape(GLint width, GLint height)
{
    const GLfloat fovy = 65.0f;
    const GLfloat near = 3.0f;
    const GLfloat far = 100.0f;

    glViewport(0, 0, width, height);

//    g_Projection = glm::perspective(fovy, (float)width / height, near, far);
    g_Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
    g_Modelview = glm::mat4();
//    g_Modelview = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -5.0f));
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // program
    g_Shader.reset(new Shader());
    g_Shader->AddShader(GL_VERTEX_SHADER, "../glut_test/shader/default.vert");
    g_Shader->AddShader(GL_FRAGMENT_SHADER, "../glut_test/shader/default.frag");
    glBindAttribLocation(g_Shader->GetProgram(), 0, "vertex");
    g_Shader->LinkProgram();
    modelview = glGetUniformLocation(g_Shader->GetProgram(), "modelview");
    projection = glGetUniformLocation(g_Shader->GetProgram(), "projection");
    color = glGetUniformLocation(g_Shader->GetProgram(), "color");

    // arc
    g_Arc.reset(new MekArc2D(40));
    g_Arc->Init(0.2f, 0.1f, 315.0f, 90.0f, 1.0f);

    glGenVertexArrays(1, &g_VAO);
    glGenBuffers(1, &g_VBO);

    glBindVertexArray(g_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    glBufferData(GL_ARRAY_BUFFER, g_Arc->GetDataSize(), g_Arc->GetData(), GL_STATIC_DRAW);

//    float *p = (float*)g_Arc->GetData();


//    for (int i = 0; i < g_Arc->GetCount(); ++i)
//    {
//        std::cerr << p[i * 3] << " " << p[i * 3 + 1] << " " << p[i * 3 + 2] << std::endl;
//    }




    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, g_Arc->GetStride(), 0);

    glBindVertexArray(0);



    glGenTextures(1, &g_FBTexture);
    glBindTexture(GL_TEXTURE_2D, g_FBTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap

    glBindTexture(GL_TEXTURE_2D, 0);

//    glGenRenderbuffers(1, &m_RB);
//    glBindRenderbuffer(GL_RENDERBUFFER, m_RB);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
//    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &g_FB);
    glBindFramebuffer(GL_FRAMEBUFFER, g_FB);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_FBTexture, 0);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RB);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE)
    {
        exit(0);
    }

//    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    g_FBProjection = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, -5.0f, 5.0f);
    g_FBModelview = glm::mat4();
}

void clean()
{
    g_Arc.reset();
    g_Shader.reset();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:             // ESCAPE key
        exit(0);
        break;
    }
}

void draw()
{
    glViewport(0, 0, 1024, 1024);

    glBindFramebuffer(GL_FRAMEBUFFER, g_FB);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(g_Shader->GetProgram());
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(g_FBProjection));
    glUniformMatrix4fv(modelview, 1, GL_FALSE, glm::value_ptr(g_FBModelview));
    glUniform4fv(color, 1, glm::value_ptr(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));

    glBindVertexArray(g_VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, g_Arc->GetCount());

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindTexture(GL_TEXTURE_2D, g_FBTexture);
    glGenerateMipmap(GL_TEXTURE_2D);


    unsigned char *data = new unsigned char[1024 * 1024 * 4];

    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(g_Projection));
//    glUniformMatrix4fv(modelview, 1, GL_FALSE, glm::value_ptr(g_Modelview));
//    glUniform4fv(color, 1, glm::value_ptr(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));

    glBindVertexArray(g_VAO);
    glDrawArrays(g_Arc->GetOpenGLDrawType(), 0, g_Arc->GetCount());

    ilEnable(IL_FILE_OVERWRITE);
    g_ILTexture = ilGenImage();
    ilBindImage(g_ILTexture);
    ilTexImage(1024, 1024, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, data);

    delete [] data;

    bool t = ilSaveImage("test000123.bmp");

    ILenum te = ilGetError();

    ilDeleteImage(g_ILTexture);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glutSwapBuffers();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("glut_test");

    glewInit();
    ilInit();
    init();

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
/*	glutMouseFunc (MouseButton);
    glutMotionFunc (MouseMotion);
    glutIdleFunc (AnimateScene)*/;
    glutMainLoop();

    return 0;
}

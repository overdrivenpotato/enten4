#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>

GLuint compileVertexShader(const char* shaderSource);
GLuint compileFragmentShader(const char* shaderSource);
GLuint createVertFragShader(const char* vertexShader, const char* fragmentShader);

#endif // SHADERS_H

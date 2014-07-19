#include "shaders.h"
#include <stdexcept>
#include <vector>
#include <string>

GLuint compileShader(const char* shaderSource, GLint type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success) return shader;

    // Cleanup
    glDeleteShader(shader);

    GLint logLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> message(logLength);
    glGetShaderInfoLog(shader, logLength, NULL, &message[0]);

    throw std::logic_error(std::string("Error compiling shader: ") + &message[0]);
}

GLuint compileVertexShader(const char *shaderSource) {
    return compileShader(shaderSource, GL_VERTEX_SHADER);
}

GLuint compileFragmentShader(const char *shaderSource) {
    return compileShader(shaderSource, GL_FRAGMENT_SHADER);
}

GLuint createVertFragShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
    GLuint vertexShader = compileVertexShader(vertexShaderSource);
    GLuint fragmentShader = compileFragmentShader(fragmentShaderSource);

    GLuint shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);

    // TODO: remove + make dynamic
    glBindAttribLocation(shader, 0, "position");
    glBindAttribLocation(shader, 1, "color");

    glLinkProgram(shader);

    GLint success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if(success) return shader;

    // Cleanup
    glDeleteProgram(shader);

    GLint logLength;
    glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<GLchar> message(logLength);
    glGetProgramInfoLog(shader, logLength, NULL, &message[0]);

    throw std::logic_error(std::string("Error linking shader: ") + &message[0]);
}

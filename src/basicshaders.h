#ifndef BASICSHADERS_H
#define BASICSHADERS_H

//#define GLSL(src) "#version 150 core\n" #src
#define GLSL_directive(data) "#" #data "\n"
#define GLSL(data) #data

const char* vertexShader2D =
    GLSL_directive(version 130)
    GLSL(
        in vec3 position;
        in vec3 color;

        uniform mat4 MVP;

        out vec3 outColor;

        void main() {
            outColor = color;
            gl_Position = MVP * vec4(position, 1.0);
        }
);

const char* whiteFragment =
    GLSL_directive(version 130)
    GLSL(
        in vec3 outColor;
        out vec3 color;

        void main() {
            color = outColor;
        }
);

#endif // BASICSHADERS_H

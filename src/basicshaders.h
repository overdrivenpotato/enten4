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
        in vec2 texUVin;

        uniform mat4 MVP;

        out vec3 outColor;
        out vec2 texUV;

        void main() {
            outColor = color;
            texUV = texUVin;
            gl_Position = MVP * vec4(position, 1.0);
        }
);

const char* whiteFragment =
    GLSL_directive(version 130)
    GLSL(
        in vec3 outColor;
        in vec2 texUV;

        out vec4 color;

        uniform sampler2D tex;

        void main() {
            color = texture(tex, texUV) * 0.5 + 0.5 * vec4(outColor, 1);
        }
);

#endif // BASICSHADERS_H

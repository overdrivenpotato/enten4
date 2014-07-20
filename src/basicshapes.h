#ifndef BASICSHAPES_H
#define BASICSHAPES_H

#include <vector>

namespace basicmesh {
    const float rawCube[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
         1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f
    };
    const std::vector<float> cube(rawCube, rawCube + (sizeof(rawCube) / sizeof(float)));

    const float cubeUVraw[] = {
        1, 0,
        1, 1,
        0, 1,
        0, 1,
        0, 0,
        1, 0,

        1, 0,
        1, 1,
        0, 1,
        0, 1,
        0, 0,
        1, 0,

        1, 0,
        1, 1,
        0, 1,
        0, 1,
        0, 0,
        1, 0,

        1, 0,
        1, 1,
        0, 1,
        0, 1,
        0, 0,
        1, 0,

        1, 0,
        1, 1,
        0, 1,
        0, 1,
        0, 0,
        1, 0,

        1, 0,
        1, 1,
        0, 1,
        0, 1,
        0, 0,
        1, 0,

    };
    const std::vector<float> cubeUV(cubeUVraw, cubeUVraw + sizeof(cubeUVraw) / sizeof(float));

    const float rawTriangle[] = {
    //   X      Y     Z
        -1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
    };
    const std::vector<float> triangle(rawTriangle, rawTriangle + (sizeof(rawTriangle) / sizeof(float)));

    const float rawPlane[] = {
         1.0f, 0.0f,  1.0f,
         1.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, -1.0f,
        -1.0f, 0.0f,  1.0f,
         1.0f, 0.0f,  1.0f,
    };
    const std::vector<float> meshPlane(rawPlane, rawPlane + (sizeof(rawPlane) / sizeof(float)));

    const float planeUVraw[] = {
        1, 0,
        1, 1,
        0, 1,
        0, 1,
        0, 0,
        1, 0
    };
    const std::vector<float> planeUV(planeUVraw, planeUVraw + sizeof(planeUVraw) / sizeof(float));
}

#endif // BASICSHAPES_H

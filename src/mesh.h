#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(std::vector<float> vertices, std::vector<float> colorData, std::vector<float> uvData);
    ~Mesh();

    void draw();
private:
    GLuint vertBuffer;
    GLuint colorBuffer;
    GLuint uvBuffer;
    std::vector<float> vertices;
    std::vector<float> colorData;
    std::vector<float> uvData;
    GLuint vba;
    glm::mat4 model;
};

#endif // MESH_H

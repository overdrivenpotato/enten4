#include "mesh.h"

Mesh::Mesh(std::vector<float> vertices, std::vector<float> colorData):
vertices(vertices),
colorData(colorData),
model(1.0f) {
    glGenVertexArrays(1, &vba);
    glBindVertexArray(vba);

    glGenBuffers(1, &vertBuffer);
    glGenBuffers(1, &colorBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(float), &colorData[0], GL_STATIC_DRAW);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vertBuffer);
    glDeleteBuffers(1, &colorBuffer);
}

void Mesh::draw() {
    glBindVertexArray(vba);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

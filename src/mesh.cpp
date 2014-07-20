#include "mesh.h"

Mesh::Mesh(std::vector<float> vertices, std::vector<float> colorData, std::vector<float> uvData):
vertices(vertices),
colorData(colorData),
uvData(uvData),
model(1.0f) {
    glGenVertexArrays(1, &vba);
    glBindVertexArray(vba);

    glGenBuffers(1, &vertBuffer);
    glGenBuffers(1, &colorBuffer);
    glGenBuffers(1, &uvBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colorData.size() * sizeof(float), &colorData[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(float), &uvData[0], GL_STATIC_DRAW);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vertBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteBuffers(1, &uvBuffer);
}

void Mesh::draw() {
    glBindVertexArray(vba);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}

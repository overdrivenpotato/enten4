#define _USE_MATH_DEFINES
#include <cmath>
#define GLM_FORCE_RADIANS
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera(): upVector(0, 1, 0) {}

CameraFP::CameraFP(glm::vec3 position, glm::vec3 direction):
position(position),
pointer(direction),
cachedMatrix(glm::lookAt(position, direction, upVector)),
pitchRadians(0) {
    pointer = glm::normalize(pointer);
    sideVector = glm::rotate(glm::vec3(pointer.x, 0, pointer.z), (float)M_PI / 2.f, upVector);
}

CameraFP::~CameraFP() {}

void CameraFP::translate(glm::vec3 movement) {
    position += movement;
    recalcViewMatrix();
}

void CameraFP::translateRelative(glm::vec3 movement) {
    glm::vec2 rel = glm::normalize(glm::vec2(pointer.x, pointer.z));
    float angle = atan2(rel.x, rel.y);
    translate(glm::rotate(movement, angle, upVector));
}

void CameraFP::rotateYaw(float angleRadians) {
    sideVector = glm::rotate(sideVector, angleRadians, upVector);
    pointer = glm::rotate(pointer, angleRadians, upVector);
    recalcViewMatrix();
}

void CameraFP::rotatePitch(float angleRadians) {
    float result = pitchRadians + angleRadians;

    if(result > M_PI / 2 || result < -M_PI / 2) {
        return;
    }

    pitchRadians = result;
    pointer = glm::rotate(pointer, angleRadians, sideVector);
    recalcViewMatrix();
}

void CameraFP::recalcViewMatrix() {
    pointer = glm::normalize(pointer);
    cachedMatrix = glm::lookAt(position, position + pointer, upVector);
}

glm::mat4 CameraFP::getViewMatrix() {
    return cachedMatrix;
}

glm::vec3 CameraFP::getDirection() {
    return pointer;
}

glm::vec3 CameraFP::getCoords() {
    return position;
}

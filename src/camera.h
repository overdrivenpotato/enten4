#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    virtual void translate(glm::vec3 movement) = 0;
    virtual void translateRelative(glm::vec3 movement) = 0;
    virtual void rotatePitch(float angleRadians) = 0;
    virtual void rotateYaw(float angleRadians) = 0;
    virtual glm::mat4 getViewMatrix() = 0;
    virtual glm::vec3 getDirection() = 0;
    virtual glm::vec3 getCoords() = 0;
protected:
    const glm::vec3 upVector;
};

class CameraFP: public Camera {
public:
    CameraFP(glm::vec3 position, glm::vec3 direction);
    ~CameraFP();

    virtual void translate(glm::vec3 movement);
    virtual void translateRelative(glm::vec3 movement);
    virtual void rotatePitch(float angleRadians);
    virtual void rotateYaw(float angleRadians);
    void recalcViewMatrix();
    virtual glm::mat4 getViewMatrix();
    virtual glm::vec3 getDirection();
    virtual glm::vec3 getCoords();
private:
    glm::vec3 position;
    glm::vec3 pointer;
    glm::mat4 cachedMatrix;
    glm::vec3 sideVector;
    float pitchRadians;
};

#endif // CAMERA_H

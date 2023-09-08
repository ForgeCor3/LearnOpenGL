#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position,
               glm::vec3 front,
               glm::vec3 _worldUp,
               float _yaw, float _pitch)
: cameraPosition(position),
  cameraFront(front),
  worldUp(_worldUp),
  yaw(_yaw),
  pitch(_pitch)
{
    cameraFov = 45.0f;
    updateCameraVectors();
}

Camera::~Camera() {}

glm::mat4 Camera::getLookAt()
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void Camera::processKeyboard(cameraMovement direction, float dt)
{
    float velocity = SPEED * dt;

    if(direction == FORWARD)
        cameraPosition += velocity * cameraFront;
    if(direction == RIGHT)
        cameraPosition += velocity * cameraRight; 
    if(direction == BACKWARD)
        cameraPosition -= velocity * cameraFront;
    if(direction == LEFT)
        cameraPosition -= velocity * cameraRight;
}

void Camera::processMouseInput(float xOffset, float yOffset)
{
    xOffset *= MOUSE_SENSITIVITY;
    yOffset *= MOUSE_SENSITIVITY;

    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset)
{
    cameraFov -= (float)yOffset;
    if(cameraFov < 1.0f)
        cameraFov = 1.0f;
    if(cameraFov > 45.0f)
        cameraFov = 45.0f;
}

float Camera::getFov()
{
    return cameraFov;
}

void Camera::updateCameraVectors()
{
    cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront.y = sin(glm::radians(pitch));
    cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::normalize(cameraFront);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
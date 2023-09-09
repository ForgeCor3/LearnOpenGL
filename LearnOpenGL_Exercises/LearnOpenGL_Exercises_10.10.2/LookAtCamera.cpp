#include "LookAtCamera.h"

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
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::mat4 translation = glm::mat4(1.0f);

    rotation[0][0] = cameraRight.x;
    rotation[1][0] = cameraRight.y;
    rotation[2][0] = cameraRight.z;

    rotation[0][1] = cameraUp.x;
    rotation[1][1] = cameraUp.y;
    rotation[2][1] = cameraUp.z;

    rotation[0][2] = -cameraFront.x;
    rotation[1][2] = -cameraFront.y;
    rotation[2][2] = -cameraFront.z;

    translation[3][0] = -cameraPosition.x;
    translation[3][1] = -cameraPosition.y;
    translation[3][2] = -cameraPosition.z;

    return rotation * translation;
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
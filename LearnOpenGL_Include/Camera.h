#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum cameraMovement
{
    FORWARD = 0,
    RIGHT = 1,
    BACKWARD = 2,
    LEFT = 3
};

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
            float _yaw = -90.0f, float _pitch = 0.0f);
    ~Camera();

    glm::mat4 getLookAt();

    void processKeyboard(cameraMovement direction, float dt);
    void processMouseInput(float xOffset, float yOffset);
    void processMouseScroll(float yOffset);

    float getFov();
    glm::vec3 getPosition();
    
private:
    void updateCameraVectors();

    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraRight;
    glm::vec3 cameraUp;

    glm::vec3 worldUp;

    float cameraFov;
    float yaw;
    float pitch;

    const float SPEED = 2.5f;
    const float MOUSE_SENSITIVITY = 0.1f;
    const float MAX_ZOOM_FOV = 45.0f;
};
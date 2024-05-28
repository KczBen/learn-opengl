#if !defined(CAMERA_H)
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum MOVEMENT_DIRECTION {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class Camera {
    public:
        glm::vec3 position;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;
        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float movementSpeed;
        float mouseSensitivity;
        float FoV;

        // Vector constructor
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : position(glm::vec3(0.0f, 0.0f, 0.0f)),
                    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), 
                    movementSpeed(SPEED), 
                    mouseSensitivity(SENSITIVITY), 
                    worldUp(up),
                    FoV(FOV),
                    yaw(YAW),
                    pitch(PITCH){
            updateCameraVectors();
        }

        // Scalar constructor
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : position(glm::vec3(posX, posY, posZ)),
                    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), 
                    movementSpeed(SPEED), 
                    mouseSensitivity(SENSITIVITY), 
                    worldUp(glm::vec3(upX, upY, upZ)),
                    FoV(FOV),
                    yaw(YAW),
                    pitch(PITCH){ 
            updateCameraVectors();
        }

        glm::mat4 getViewMatrix() {
            return glm::lookAt(position, position + cameraFront, cameraUp);
        }

        void processKeyboard(MOVEMENT_DIRECTION direction, float deltaTime) {
            float velocity = movementSpeed * deltaTime;
            if (direction == FORWARD) {
                position += cameraFront * velocity;
            }

            if (direction == BACKWARD) {
                position -= cameraFront * velocity;
            }

            if (direction == LEFT) {
                position -= cameraRight * velocity;
            }

            if (direction == RIGHT) {
                position += cameraRight * velocity;
            }
        }

        void processMouse(float xOffset, float yOffset, GLboolean constrainPitch = true) {
            xOffset *= mouseSensitivity;
            yOffset *= mouseSensitivity;

            yaw += xOffset;
            pitch += yOffset;

            if (constrainPitch) {
                if (pitch >= 89.9f) {
                    pitch = 89.9f;
                }

                if (pitch <= -89.9) {
                    pitch = -89.9f;
                }
            }

            updateCameraVectors();
        }

    private:
        void updateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

            cameraFront = glm::normalize(front);

            cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
            cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
        }
};
#endif // CAMERA_H

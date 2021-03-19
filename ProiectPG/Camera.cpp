#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        
        if (direction == MOVE_FORWARD) {
            this->cameraPosition += speed * this->cameraFrontDirection;
            this->cameraTarget += speed * this->cameraFrontDirection;
        }
        if (direction == MOVE_BACKWARD) {
            this->cameraPosition -= speed * this->cameraFrontDirection;
            this->cameraTarget -= speed * this->cameraFrontDirection;
        }
        if (direction == MOVE_LEFT) {
            this->cameraPosition -= speed * this->cameraRightDirection;
            this->cameraTarget -= speed * this->cameraRightDirection;
        }
        if (direction == MOVE_RIGHT) {
            this->cameraPosition += speed * this->cameraRightDirection;
            this->cameraTarget += speed * this->cameraRightDirection;
        }
        if (direction == MOVE_UP) {
            this->cameraPosition += speed * this->cameraUpDirection;
            this->cameraTarget += speed * this->cameraUpDirection;

        }
        if (direction == MOVE_DOWN) {
            this->cameraPosition -= speed * this->cameraUpDirection;
            this->cameraTarget -= speed * this->cameraUpDirection;
        }

    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        this->cameraFrontDirection = glm::normalize(direction);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
    }

    void Camera::setCameraTarget(glm::vec3 origin) {
        this->cameraTarget = origin;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
    }
}
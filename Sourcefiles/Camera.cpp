#include "../Headerfiles/Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspectRatio, float nearClip, float farClip) {
    this->position = position;
    this->target = target;
    this->up = up;
    updateViewMatrix();

    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->nearClip = nearClip;
    this->farClip = farClip;
    updateProjectionMatrix();
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
    updateViewMatrix();
}

void Camera::setTarget(glm::vec3 target) {
    this->target = target;
    updateViewMatrix();
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    updateProjectionMatrix();
}

glm::mat4 Camera::getViewMatrix() const {
    return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return this->projectionMatrix;
}

void Camera::updateViewMatrix() {
    this->viewMatrix = glm::lookAt(this->position, this->target, this->up);
}

void Camera::updateProjectionMatrix() {
    this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->aspectRatio, this->nearClip, this->farClip);
}

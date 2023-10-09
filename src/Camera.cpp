//
// Created by theo on 15/08/23.
//

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::updateView() {
    m_view = glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::updateProjection() {
    m_projection = glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::init(int width, int height) {
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_fov = 3.141592653589793238462643383279/2.0f;
    m_aspect = (float) width / (float) height;
    m_near = 0.1f;
    m_far = 1000.0f;

    updateView();
    updateProjection();
}

Camera::CameraProperties Camera::getCameraProperties() {
    return {
        m_position,
        m_direction
    };
}
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

void Camera::init() {
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_fov = 45.0f;
    m_aspect = 1.0f;
    m_near = 0.1f;
    m_far = 100.0f;

    updateView();
    updateProjection();
}
//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_CAMERA_H
#define GL_PBR_TRAINING_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 m_position{};
    glm::vec3 m_direction{};
    glm::vec3 m_up{};

    float m_fov{};
    float m_aspect{};
    float m_near{};
    float m_far{};

    glm::mat4 m_view{};
    glm::mat4 m_projection{};

    void updateView();
    void updateProjection();

    void init(int width, int height);
};


#endif //GL_PBR_TRAINING_CAMERA_H

//
// Created by theo on 17/08/23.
//

#ifndef GL_PBR_TRAINING_SKYBOX_H
#define GL_PBR_TRAINING_SKYBOX_H

#include "Shader.h"

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

class Skybox {
private:
    Shader m_shader;

    GLuint m_vao, m_vbo, m_cubemap;

    glm::mat4 m_model;
public:
    struct CubemapInfo {
        std::string negx;
        std::string negy;
        std::string negz;
        std::string posx;
        std::string posy;
        std::string posz;
    };

    static Skybox load(CubemapInfo faces);

    GLuint getCubemap() const;

    void draw(glm::mat4 view, glm::mat4 projection) const;
};


#endif //GL_PBR_TRAINING_SKYBOX_H

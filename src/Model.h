//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_MODEL_H
#define GL_PBR_TRAINING_MODEL_H

#include "Material.h"

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>

class Model {
private:
    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_ebo{};

    GLuint m_num_indices{};

    Material *m_material;

public:
    glm::vec3 m_position{};
    glm::vec3 m_rotation{};
    glm::vec3 m_scale{1.0f, 1.0f, 1.0f};

    glm::mat4 m_model_matrix;

    void load(const std::string &path);

    void setMaterial(Material &material);

    void draw(glm::mat4 view, glm::mat4 projection) const;

    void setNumIndices(GLuint num_indices);

    void updateModelMatrix();

    glm::mat4 getModelMatrix() const;
};


#endif //GL_PBR_TRAINING_MODEL_H

//
// Created by theo on 16/08/23.
//

#ifndef GL_PBR_TRAINING_MATERIAL_H
#define GL_PBR_TRAINING_MATERIAL_H

#include "Shader.h"

#include <GL/glew.h>

#include <vector>
#include <string>

#include <glm/glm.hpp>

class Material {
private:
    Shader m_shader;

    std::vector<GLuint> m_textures{};
    std::vector<std::string> m_texture_uniforms{};

    std::vector<glm::vec3> m_vec3_parameters{};
    std::vector<std::string> m_vec3_parameters_uniforms{};
    std::vector<glm::vec2> m_vec2_parameters{};
    std::vector<std::string> m_vec2_parameters_uniforms{};
    std::vector<float> m_float_parameters{};
    std::vector<std::string> m_float_parameters_uniforms{};
    std::vector<glm::vec4> m_vec4_parameters{};
    std::vector<std::string> m_vec4_parameters_uniforms{};
public:
    void setShader(Shader shader);

    void use();

    void setParameter(const std::string& param, float value);
    void setParameter(const std::string& param, glm::vec2 value);
    void setParameter(const std::string& param, glm::vec3 value);
    void setParameter(const std::string& param, glm::vec4 value);

    float getFloatParameter(const std::string& param);
    glm::vec2 getVec2Parameter(const std::string& param);
    glm::vec3 getVec3Parameter(const std::string& param);
    glm::vec4 getVec4Parameter(const std::string& param);
};


#endif //GL_PBR_TRAINING_MATERIAL_H

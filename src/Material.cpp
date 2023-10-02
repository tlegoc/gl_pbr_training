//
// Created by theo on 16/08/23.
//

#include "Material.h"

void Material::setShader(Shader shader) {
    m_shader = shader;
}

void Material::use() {
    m_shader.use();

    for (int i = 0; i < m_textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);
        glUniform1i(glGetUniformLocation(m_shader.getProgram(), m_texture_uniforms[i].c_str()), i);
    }

    for (int i = 0; i < m_float_parameters.size(); ++i) {
        glUniform1f(glGetUniformLocation(m_shader.getProgram(), m_float_parameters_uniforms[i].c_str()), m_float_parameters[i]);
    }
}

void Material::setParameter(std::string param, float value) {
    if (std::find(m_float_parameters_uniforms.begin(), m_float_parameters_uniforms.end(), param) != m_float_parameters_uniforms.end()) {
        m_float_parameters[std::find(m_float_parameters_uniforms.begin(), m_float_parameters_uniforms.end(), param) - m_float_parameters_uniforms.begin()] = value;
    } else {
        m_float_parameters.push_back(value);
        m_float_parameters_uniforms.emplace_back(param.c_str());
    }
}

void Material::setParameter(std::string param, glm::vec2 value) {
    if (std::find(m_vec2_parameters_uniforms.begin(), m_vec2_parameters_uniforms.end(), param) != m_vec2_parameters_uniforms.end()) {
        m_vec2_parameters[std::find(m_vec2_parameters_uniforms.begin(), m_vec2_parameters_uniforms.end(), param) - m_vec2_parameters_uniforms.begin()] = value;
    } else {
        m_vec2_parameters.push_back(value);
        m_vec2_parameters_uniforms.emplace_back(param.c_str());
    }
}

void Material::setParameter(std::string param, glm::vec3 value) {
    if (std::find(m_vec3_parameters_uniforms.begin(), m_vec3_parameters_uniforms.end(), param) != m_vec3_parameters_uniforms.end()) {
        m_vec3_parameters[std::find(m_vec3_parameters_uniforms.begin(), m_vec3_parameters_uniforms.end(), param) - m_vec3_parameters_uniforms.begin()] = value;
    } else {
        m_vec3_parameters.push_back(value);
        m_vec3_parameters_uniforms.emplace_back(param.c_str());
    }
}

void Material::setParameter(std::string param, glm::vec4 value) {
    if (std::find(m_vec4_parameters_uniforms.begin(), m_vec4_parameters_uniforms.end(), param) != m_vec4_parameters_uniforms.end()) {
        m_vec4_parameters[std::find(m_vec4_parameters_uniforms.begin(), m_vec4_parameters_uniforms.end(), param) - m_vec4_parameters_uniforms.begin()] = value;
    } else {
        m_vec4_parameters.push_back(value);
        m_vec4_parameters_uniforms.emplace_back(param.c_str());
    }
}

float Material::getFloatParameter(std::string param) {
    return m_float_parameters[std::find(m_float_parameters_uniforms.begin(), m_float_parameters_uniforms.end(), param) - m_float_parameters_uniforms.begin()];
}

glm::vec2 Material::getVec2Parameter(std::string param) {
    return m_vec2_parameters[std::find(m_vec2_parameters_uniforms.begin(), m_vec2_parameters_uniforms.end(), param) - m_vec2_parameters_uniforms.begin()];
}

glm::vec3 Material::getVec3Parameter(std::string param) {
    return m_vec3_parameters[std::find(m_vec3_parameters_uniforms.begin(), m_vec3_parameters_uniforms.end(), param) - m_vec3_parameters_uniforms.begin()];
}

glm::vec4 Material::getVec4Parameter(std::string param) {
    return m_vec4_parameters[std::find(m_vec4_parameters_uniforms.begin(), m_vec4_parameters_uniforms.end(), param) - m_vec4_parameters_uniforms.begin()];
}
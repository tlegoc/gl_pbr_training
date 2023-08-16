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
}
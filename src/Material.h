//
// Created by theo on 16/08/23.
//

#ifndef GL_PBR_TRAINING_MATERIAL_H
#define GL_PBR_TRAINING_MATERIAL_H

#include "Shader.h"

#include <GL/glew.h>

#include <vector>
#include <string>

class Material {
private:
    Shader m_shader;

    std::vector<GLuint> m_textures{};
    std::vector<std::string> m_texture_uniforms{};
public:
    void setShader(Shader shader);

    void use();
};


#endif //GL_PBR_TRAINING_MATERIAL_H

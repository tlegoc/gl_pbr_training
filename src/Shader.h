//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_SHADER_H
#define GL_PBR_TRAINING_SHADER_H

#include <GL/glew.h>

class Shader {
private:
    GLuint m_program{};

    GLuint m_vertex_shader{};
    GLuint m_fragment_shader{};

public:
    static Shader load(const char *vertex_shader_path, const char *fragment_shader_path);

    GLuint getProgram() const;

    void use();
};


#endif //GL_PBR_TRAINING_SHADER_H

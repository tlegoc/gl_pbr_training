//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_PBRDEFERREDPASS_H
#define GL_PBR_TRAINING_PBRDEFERREDPASS_H

#include "../RenderGraph.h"

#include "../Shader.h"

#include <GL/glew.h>

class PBRDeferredPass : public Pass {
private:
    GLuint m_input_framebuffer{};

    GLuint m_vao{};
    GLuint m_vbo{};

    Shader m_shader;

public:
    void init() override;

    void setInputFramebuffer(GLuint framebuffer);

    void execute() override;
};


#endif //GL_PBR_TRAINING_PBRDEFERREDPASS_H

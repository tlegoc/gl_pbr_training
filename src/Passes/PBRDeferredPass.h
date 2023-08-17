//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_PBRDEFERREDPASS_H
#define GL_PBR_TRAINING_PBRDEFERREDPASS_H

#include "../RenderGraph.h"
#include "../Framebuffer.h"
#include "../Shader.h"

#include <GL/glew.h>

class PBRDeferredPass : public Pass {
private:
    const Framebuffer *m_input_framebuffer{};

    Shader m_shader;

    GLuint m_vao, m_vbo;

public:
    void init() override;

    void setInputFramebuffer(const Framebuffer *framebuffer);

    void execute() override;
};


#endif //GL_PBR_TRAINING_PBRDEFERREDPASS_H

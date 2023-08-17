//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_PBRDEFERREDPASS_H
#define GL_PBR_TRAINING_PBRDEFERREDPASS_H

#include "../RenderGraph.h"
#include "../Framebuffer.h"
#include "../Shader.h"
#include "../Skybox.h"
#include "../Camera.h"

#include <GL/glew.h>

class PBRDeferredPass : public Pass {
private:
    const Framebuffer *m_input_framebuffer{};

    Shader m_shader;

    const Skybox *m_skybox;

    GLuint m_vao, m_vbo;

    const Camera *m_camera;
public:
    void init() override;

    void setInputFramebuffer(const Framebuffer *framebuffer);

    void execute() override;

    void setSkybox(const Skybox *skybox);

    void setCamera(const Camera *camera);
};


#endif //GL_PBR_TRAINING_PBRDEFERREDPASS_H

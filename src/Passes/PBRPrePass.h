//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_PBRPREPASS_H
#define GL_PBR_TRAINING_PBRPREPASS_H

#include "../RenderGraph.h"
#include "../Framebuffer.h"
#include "../Camera.h"
#include "../Model.h"

#include <GL/glew.h>

class PBRPrePass : public Pass {
private:
    Framebuffer m_output_framebuffer{};

//    GLuint m_texture_base_color{};
//    GLuint m_texture_metallic{};
//    GLuint m_texture_roughness{};
//    GLuint m_texture_reflectance{};
//    GLuint m_texture_emissive{};
//    GLuint m_texture_normal{};
//    GLuint m_texture_ao{};
//    GLuint m_depth_buffer{};

    std::vector<Model*> m_models;
public:
    const Camera *m_camera;

    void init() override;

    const Framebuffer *getOutputFramebuffer() const;

    void addModel(Model *model);

    void setCamera(const Camera *camera);

    void execute() override;
};


#endif //GL_PBR_TRAINING_PBRPREPASS_H

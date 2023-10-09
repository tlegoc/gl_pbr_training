//
// Created by theo on 15/08/23.
//

#include "PBRPrePass.h"

#include <GL/glew.h>

#include <iostream>

void PBRPrePass::init(int width, int height) {
    std::cout << "\t-- Initializing PBR Prepass" << std::endl;

    m_output_framebuffer.setSize(width, height);

    // Color
    m_output_framebuffer.addTexture(GL_RGBA);
    // Metallic : Roughness : Reflectance
    m_output_framebuffer.addTexture(GL_RGB16F);
    // Emmissive
    m_output_framebuffer.addTexture(GL_RGB);
    // Normal
    m_output_framebuffer.addTexture(GL_RGB16F);
    // Position
    m_output_framebuffer.addTexture(GL_RGB16F);
    // Occlusion : Clearcoat : Clearcoat Roughness
    m_output_framebuffer.addTexture(GL_RGB16F);

    m_output_framebuffer.init();

    std::cout << "\t-- Initializing done" << std::endl;
}

const Framebuffer *PBRPrePass::getOutputFramebuffer() const {
    return &m_output_framebuffer;
}

void PBRPrePass::addModel(Model *model) {
    m_models.push_back(model);
}

void PBRPrePass::setCamera(const Camera *camera) {
    m_camera = camera;
}

void PBRPrePass::execute() {
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    m_output_framebuffer.use();

    glm::mat4 view = m_camera->m_view;
    glm::mat4 projection = m_camera->m_projection;

    for (auto model: m_models) {
        model->draw(view, projection);
    }
}
//
// Created by theo on 15/08/23.
//

#include "PBRPrePass.h"

#include <GL/glew.h>

#include <iostream>

void PBRPrePass::init() {
    std::cout << "\t-- Initializing PBR Prepass" << std::endl;

    m_output_framebuffer.setSize(800, 800);

    m_output_framebuffer.addTexture(GL_RGBA);
    m_output_framebuffer.addTexture(GL_RGB16F);
    m_output_framebuffer.addTexture(GL_RGB);
    m_output_framebuffer.addTexture(GL_RGB16F);
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
    m_output_framebuffer.use();

    glm::mat4 view = m_camera->m_view;
    glm::mat4 projection = m_camera->m_projection;

    for (auto model: m_models) {
        model->draw(view, projection);
    }
}
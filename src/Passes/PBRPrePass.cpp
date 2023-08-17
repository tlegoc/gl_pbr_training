//
// Created by theo on 15/08/23.
//

#include "PBRPrePass.h"

#include <GL/glew.h>

#include <iostream>

void PBRPrePass::init() {
    std::cout << "\t-- Initializing PBR Prepass" << std::endl;

    m_output_framebuffer.setSize(800, 600);

    m_output_framebuffer.addTexture(GL_RGB);
    m_output_framebuffer.addTexture(GL_R16F);
    m_output_framebuffer.addTexture(GL_R16F);
    m_output_framebuffer.addTexture(GL_R16F);
    m_output_framebuffer.addTexture(GL_RGB);
    m_output_framebuffer.addTexture(GL_RGB16F);
    m_output_framebuffer.addTexture(GL_R16F);

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

    GLenum draw_buffers[7] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3,
            GL_COLOR_ATTACHMENT4,
            GL_COLOR_ATTACHMENT5,
            GL_COLOR_ATTACHMENT6
    };

    glDrawBuffers(7, draw_buffers);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = m_camera->m_view;
    glm::mat4 projection = m_camera->m_projection;

    for (auto model: m_models) {
        model->draw(view, projection);
    }
}
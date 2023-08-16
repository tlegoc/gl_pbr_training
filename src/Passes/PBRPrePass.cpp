//
// Created by theo on 15/08/23.
//

#include "PBRPrePass.h"

#include <GL/glew.h>

#include <iostream>

void PBRPrePass::init() {
    std::cout << "\t-- Initializing PBR Prepass" << std::endl;

    glGenFramebuffers(1, &m_output_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_output_framebuffer);

    glGenTextures(1, &m_texture_base_color);
    glBindTexture(GL_TEXTURE_2D, m_texture_base_color);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture_base_color, 0);

    glGenTextures(1, &m_texture_metallic);
    glBindTexture(GL_TEXTURE_2D, m_texture_metallic);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, m_texture_metallic, 0);

    glGenTextures(1, &m_texture_roughness);
    glBindTexture(GL_TEXTURE_2D, m_texture_roughness);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, m_texture_roughness, 0);

    glGenTextures(1, &m_texture_reflectance);
    glBindTexture(GL_TEXTURE_2D, m_texture_reflectance);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, m_texture_reflectance, 0);

    glGenTextures(1, &m_texture_emissive);
    glBindTexture(GL_TEXTURE_2D, m_texture_emissive);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, m_texture_emissive, 0);

    glGenTextures(1, &m_texture_normal);
    glBindTexture(GL_TEXTURE_2D, m_texture_normal);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, m_texture_normal, 0);

    glGenTextures(1, &m_texture_ao);
    glBindTexture(GL_TEXTURE_2D, m_texture_ao);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, m_texture_ao, 0);

    glGenRenderbuffers(1, &m_depth_buffer);

    glBindRenderbuffer(GL_RENDERBUFFER, m_depth_buffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth_buffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Framebuffer not complete");

    std::cout << "\t-- Initializing done" << std::endl;
}

GLuint PBRPrePass::getOutputFramebuffer() const {
    return m_output_framebuffer;
}

void PBRPrePass::addModel(Model *model) {
    m_models.push_back(model);
}

void PBRPrePass::setCamera(const Camera *camera) {
    m_camera = camera;
}

void PBRPrePass::execute() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_output_framebuffer);

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

    for (auto model : m_models) {
        model->draw(view, projection);
    }
}
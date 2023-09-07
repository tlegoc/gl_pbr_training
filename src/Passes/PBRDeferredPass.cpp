//
// Created by theo on 15/08/23.
//

#include "PBRDeferredPass.h"

#include <iostream>

void PBRDeferredPass::init() {
    std::cout << "\t-- Initializing PBR Deferred pass" << std::endl;

    const GLfloat vertices[] = {
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_shader = Shader::load("shaders/core/passthrough.vert", "shaders/core/pbr_deferred_pass.frag");

    m_shader.use();
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_base_color"), 0);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_met_rough_ref"), 1);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_emissive"), 2);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_normal"), 3);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_position"), 4);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_occ_cc_ccrough"), 5);
    glUseProgram(0);

    std::cout << "\t-- Initializing done" << std::endl;
}

void PBRDeferredPass::setInputFramebuffer(const Framebuffer *framebuffer) {
    m_input_framebuffer = framebuffer;
}

void PBRDeferredPass::execute() {
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glm::mat4 view = m_camera->m_view;
    glm::mat4 projection = m_camera->m_projection;

    if (m_skybox) m_skybox->draw(view, projection);

    m_shader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_input_framebuffer->getTexture(0));

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_input_framebuffer->getTexture(1));

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_input_framebuffer->getTexture(2));

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_input_framebuffer->getTexture(3));

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, m_input_framebuffer->getTexture(4));

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, m_input_framebuffer->getTexture(5));

    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox->getCubemap());

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void PBRDeferredPass::setSkybox(const Skybox *skybox) {
    m_skybox = skybox;
}

void PBRDeferredPass::setCamera(const Camera *camera) {
    m_camera = camera;
}
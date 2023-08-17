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

    m_shader = Shader::load("shaders/passthrough.vert", "shaders/pbr_deferred_pass.frag");

    m_shader.use();
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_base_color"), 0);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_metallic"), 1);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_roughness"), 2);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_reflectance"), 3);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_emissive"), 4);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_normal"), 5);
    glUniform1i(glGetUniformLocation(m_shader.getProgram(), "sampler_occlusion"), 6);
    glUseProgram(0);

    std::cout << "\t-- Initializing done" << std::endl;
}

void PBRDeferredPass::setInputFramebuffer(const Framebuffer *framebuffer) {
    m_input_framebuffer = framebuffer;
}

void PBRDeferredPass::execute() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
    glBindTexture(GL_TEXTURE_2D, m_input_framebuffer->getTexture(6));

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
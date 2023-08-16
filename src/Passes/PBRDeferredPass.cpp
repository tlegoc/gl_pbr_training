//
// Created by theo on 15/08/23.
//

#include "PBRDeferredPass.h"

#include <iostream>

void PBRDeferredPass::init() {
    // Create basic fullscreen quad
    GLfloat vertices[] = {
            -1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
            1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  1.0f, 1.0f
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

    m_shader = Shader::load("shaders/passthrough.vert", "shaders/pbr_deferred_pass.frag");
}

void PBRDeferredPass::setInputFramebuffer(GLuint framebuffer) {
    m_input_framebuffer = framebuffer;
}

void PBRDeferredPass::execute() {

}
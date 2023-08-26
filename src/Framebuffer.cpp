//
// Created by theo on 16/08/23.
//

#include "Framebuffer.h"

#include <stdexcept>

void Framebuffer::setSize(unsigned int width, unsigned int height) {
    if (initialized) throw std::runtime_error("Framebuffer already initialized");

    m_width = width;
    m_height = height;
}

void Framebuffer::addTexture(GLint internalFormat, GLint format) {
    if (initialized) throw std::runtime_error("Framebuffer already initialized");
    if (m_attachments.size() > 8) throw std::runtime_error("Max attachment count reached");

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    m_attachments.push_back(texture);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Framebuffer::init(bool depth) {
    if (initialized) throw std::runtime_error("Framebuffer already initialized");

    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    for (int i = 0; i < m_attachments.size(); i++) {
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, m_attachments[i], 0);
    }

    if (depth) {
        glGenRenderbuffers(1, &m_depth);

        glBindRenderbuffer(GL_RENDERBUFFER, m_depth);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth);
    }

    m_depth = depth;

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Framebuffer not complete");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    initialized = true;
}

void Framebuffer::use() const {
    if (!initialized) throw std::runtime_error("Framebuffer not initialized");

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    if (m_depth) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);

    std::vector<GLenum> draw_buffers(m_attachments.size());

    for (int i = 0; i < m_attachments.size(); i++)
        draw_buffers[i] = GL_COLOR_ATTACHMENT0 + i;

    glDrawBuffers(m_attachments.size(), draw_buffers.data());


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint Framebuffer::getTexture(int i) const {
    return m_attachments[i];
}
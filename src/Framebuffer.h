//
// Created by theo on 16/08/23.
//

#ifndef GL_PBR_TRAINING_FRAMEBUFFER_H
#define GL_PBR_TRAINING_FRAMEBUFFER_H

#include <GL/glew.h>

#include <vector>

class Framebuffer {
private:
    GLuint m_framebuffer{};
    GLuint m_depth{};

    bool initialized = false;

    std::vector<GLuint> m_attachments;
public:
    void setSize(unsigned int width, unsigned int height);

    void addTexture(GLint internalFormat, GLint format = GL_RGB);

    void init(bool depth = true);

    void use() const;

    GLuint getTexture(int i) const;

    unsigned int m_width, m_height;
};


#endif //GL_PBR_TRAINING_FRAMEBUFFER_H

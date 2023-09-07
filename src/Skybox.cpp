//
// Created by theo on 17/08/23.
//

#include "Skybox.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <glm/gtc/matrix_transform.hpp>

Skybox Skybox::load(CubemapInfo faces) {
    Skybox s;

    glGenTextures(1, &s.m_cubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, s.m_cubemap);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(faces.posx.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        std::cout << "Cubemap tex failed to load at path: " << faces.posx.c_str() << std::endl;
        stbi_image_free(data);
    }

    data = stbi_load(faces.negx.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        std::cout << "Cubemap tex failed to load at path: " << faces.negx.c_str() << std::endl;
        stbi_image_free(data);
    }

    data = stbi_load(faces.posy.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        std::cout << "Cubemap tex failed to load at path: " << faces.posy.c_str() << std::endl;
        stbi_image_free(data);
    }

    data = stbi_load(faces.negy.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        std::cout << "Cubemap tex failed to load at path: " << faces.negy.c_str() << std::endl;
        stbi_image_free(data);
    }

    data = stbi_load(faces.posz.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        std::cout << "Cubemap tex failed to load at path: " << faces.posz.c_str() << std::endl;
        stbi_image_free(data);
    }

    data = stbi_load(faces.negz.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        std::cout << "Cubemap tex failed to load at path: " << faces.negz.c_str() << std::endl;
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    s.m_shader = Shader::load("shaders/core/Specific/skybox.vert", "shaders/core/Specific/skybox.frag");

    // Cube vao
    float cubeVertices[] = {
            // positions
            -1.0f, 1.0f, -1.0f, // top-left
            -1.0f, -1.0f, -1.0f, // bottom-left
            1.0f, -1.0f, -1.0f, // bottom-right
            1.0f, -1.0f, -1.0f, // bottom-right
            1.0f, 1.0f, -1.0f, // top-right
            -1.0f, 1.0f, -1.0f, // top-left
            // top face
            -1.0f, 1.0f, 1.0f, // top-left
            -1.0f, 1.0f, -1.0f, // bottom-left
            1.0f, 1.0f, -1.0f, // bottom-right
            1.0f, 1.0f, -1.0f, // bottom-right
            1.0f, 1.0f, 1.0f, // top-right
            -1.0f, 1.0f, 1.0f, // top-left
            // back face
            1.0f, 1.0f, 1.0f, // top-right
            1.0f, -1.0f, 1.0f, // bottom-right
            -1.0f, -1.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, 1.0f, // bottom-left
            -1.0f, 1.0f, 1.0f, // top-left
            1.0f, 1.0f, 1.0f, // top-right
            // bottom face
            -1.0f, -1.0f, -1.0f, // top-left
            -1.0f, -1.0f, 1.0f, // bottom-left
            1.0f, -1.0f, 1.0f, // bottom-right
            1.0f, -1.0f, 1.0f, // bottom-right
            1.0f, -1.0f, -1.0f, // top-right
            -1.0f, -1.0f, -1.0f, // top-left
            // left face
            -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, 1.0f, -1.0f, // bottom-right
            -1.0f, -1.0f, -1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, // bottom-left
            -1.0f, -1.0f, 1.0f, // top-left
            -1.0f, 1.0f, 1.0f, // top-right
            // right face
            1.0f, 1.0f, -1.0f, // top-left
            1.0f, 1.0f, 1.0f, // bottom-left
            1.0f, -1.0f, 1.0f, // bottom-right
            1.0f, -1.0f, 1.0f, // bottom-right
            1.0f, -1.0f, -1.0f, // top-right
            1.0f, 1.0f, -1.0f, // top-left
    };

    glGenBuffers(1, &s.m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, s.m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);


    glGenVertexArrays(1, &s.m_vao);
    glBindVertexArray(s.m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, s.m_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glBindVertexArray(0);

    s.m_model = glm::scale(glm::mat4(1.0), glm::vec3(500.0f));

    return s;
}

GLuint Skybox::getCubemap() const {
    return m_cubemap;
}

void Skybox::draw(glm::mat4 view, glm::mat4 projection) const {
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    m_shader.use();
    glUniformMatrix4fv(0, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(1, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(2, 1, GL_FALSE, &projection[0][0]);

    glBindVertexArray(m_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glUseProgram(0);
}
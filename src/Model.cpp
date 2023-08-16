//
// Created by theo on 15/08/23.
//

#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include "tiny_obj_loader.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

void Model::load(const std::string &path) {
    std::cout << "\t-- Loading model: " << path << std::endl;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str())) {
        std::cerr << err << std::endl;
        exit(1);
    }

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    for (const auto &shape: shapes) {
        for (const auto &index: shape.mesh.indices) {
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
            vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
            vertices.push_back(attrib.normals[3 * index.normal_index + 2]);

            vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
            vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);

            indices.push_back(indices.size());
        }
    }

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (6 * sizeof(GLfloat)));

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    setNumIndices(indices.size());

    std::cout << "\t-- Model loaded: " << path << std::endl;
}

void Model::setMaterial(Material *material) {
    m_material = material;
}

void Model::draw(glm::mat4 view, glm::mat4 projection) {
    if (m_material == nullptr) {
        std::cerr << "Model::draw() called without a material" << std::endl;
        exit(1);
    }
    m_material->use();
    glBindVertexArray(m_vao);
    glUniformMatrix4fv(0, 1, GL_FALSE, &m_model_matrix[0][0]);
    glUniformMatrix4fv(1, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(2, 1, GL_FALSE, &projection[0][0]);

    glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, nullptr);
}

void Model::setNumIndices(GLuint num_indices) {
    m_num_indices = num_indices;
}

void Model::updateModelMatrix() {
    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
    m_model_matrix = glm::rotate(m_model_matrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_model_matrix = glm::rotate(m_model_matrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    m_model_matrix = glm::rotate(m_model_matrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_model_matrix = glm::scale(m_model_matrix, m_scale);
}

glm::mat4 Model::getModelMatrix() const {
    return m_model_matrix;
}
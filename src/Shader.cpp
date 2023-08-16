//
// Created by theo on 15/08/23.
//

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader Shader::load(const char *vertex_shader_path, const char *fragment_shader_path) {
    Shader s;

    std::ifstream vertex_shader_file(vertex_shader_path);
    std::ifstream fragment_shader_file(fragment_shader_path);

    std::stringstream vertex_shader_stream;
    std::stringstream fragment_shader_stream;

    vertex_shader_stream << vertex_shader_file.rdbuf();
    fragment_shader_stream << fragment_shader_file.rdbuf();

    vertex_shader_file.close();
    fragment_shader_file.close();

    std::string vertex_shader_code = vertex_shader_stream.str();
    std::string fragment_shader_code = fragment_shader_stream.str();

    const char *vertex_shader_code_c_str = vertex_shader_code.c_str();
    const char *fragment_shader_code_c_str = fragment_shader_code.c_str();

    s.m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s.m_vertex_shader, 1, &vertex_shader_code_c_str, nullptr);
    glCompileShader(s.m_vertex_shader);

    GLint vertex_shader_compile_status;
    glGetShaderiv(s.m_vertex_shader, GL_COMPILE_STATUS, &vertex_shader_compile_status);
    if (vertex_shader_compile_status != GL_TRUE) {
        char vertex_shader_info_log[512];
        glGetShaderInfoLog(s.m_vertex_shader, 512, nullptr, vertex_shader_info_log);
        std::cout << "Vertex shader compilation failed: " << vertex_shader_info_log << std::endl;
    }

    s.m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s.m_fragment_shader, 1, &fragment_shader_code_c_str, nullptr);
    glCompileShader(s.m_fragment_shader);

    GLint fragment_shader_compile_status;
    glGetShaderiv(s.m_fragment_shader, GL_COMPILE_STATUS, &fragment_shader_compile_status);
    if (fragment_shader_compile_status != GL_TRUE) {
        char fragment_shader_info_log[512];
        glGetShaderInfoLog(s.m_fragment_shader, 512, nullptr, fragment_shader_info_log);
        std::cout << "Fragment shader compilation failed: " << fragment_shader_info_log << std::endl;
    }

    s.m_program = glCreateProgram();
    glAttachShader(s.m_program, s.m_vertex_shader);
    glAttachShader(s.m_program, s.m_fragment_shader);
    glLinkProgram(s.m_program);

    GLint program_link_status;
    glGetProgramiv(s.m_program, GL_LINK_STATUS, &program_link_status);
    if (program_link_status != GL_TRUE) {
        char program_info_log[512];
        glGetProgramInfoLog(s.m_program, 512, nullptr, program_info_log);
        std::cout << "Program linking failed: " << program_info_log << std::endl;

        exit(1);

    }

    glDeleteShader(s.m_vertex_shader);
    glDeleteShader(s.m_fragment_shader);

    return s;
}

GLuint Shader::getProgram() const {
    return m_program;
}

void Shader::use() {
    glUseProgram(m_program);
}
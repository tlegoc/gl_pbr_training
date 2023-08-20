//
// Created by theo on 15/08/23.
//

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>

//void Shader::buildGLIncludes() {
//    // Get all *.glsl file path in ./shaders/
//    for (boost::filesystem::recursive_directory_iterator end, dir("./shaders");
//         dir != end; ++dir) {
//        if (!dir->path().has_extension() || dir->path().extension().compare(".glsl") != 0) continue;
//
//        std::string path = dir->path().relative_path().c_str();
//        std::cout << "\t-- Adding file to gl virtual filesystem " << path << std::endl; // just last bit
//
//        std::ifstream code_file(dir->path().relative_path());
//        std::stringstream  code_stream;
//        code_stream << code_file.rdbuf();
//
//        code_file.close();
//
//        std::string code = code_stream.str();
//
//        glNamedStringARB(GL_SHADER_INCLUDE_ARB, path.size(), path.c_str(), code.size(), code.c_str());
//        const char * ok = glIsNamedStringARB(path.size(), path.c_str()) ? "oui" : "non";
//        std::cout <<  ok << std::endl;
//    }
//}

std::string Shader::readFile(const char *path) {
    std::ifstream file(path);

    // if file not found
    if (!file.is_open())
        throw std::runtime_error("File not found");

    std::stringstream code_stream;

    code_stream << file.rdbuf();

    file.close();

    std::string code = code_stream.str();

    return code;
}

std::string Shader::loadFilePreprocess(const std::string &source, const boost::filesystem::path &filename, int level) {
    if (level > 32)
        throw std::runtime_error("header inclusion depth limit reached, might be caused by cyclic header inclusion");
    using namespace std;

//    static const boost::regex re("^[ ]*#[ ]*include[ ]+[\"<](.*)[\">].*");
    static const boost::regex re("[ ]*#include[ ]+[\"<]([A-Za-z./]*)[\">].*");
    stringstream input;
    stringstream output;
    input << source;

    size_t line_number = 1;
    boost::smatch matches;

    string line;
    while (std::getline(input, line)) {
        if (boost::regex_search(line, matches, re)) {
            std::string include_file = matches[1];
            std::string include_string;

            include_file = filename.parent_path().string() + "/" + include_file;

            include_string = readFile(include_file.c_str());

            output << loadFilePreprocess(include_string, filename.parent_path().c_str() + include_file, level + 1) << endl;
        } else {
            output << line << endl;
        }
        ++line_number;
    }

    return output.str();
}

Shader Shader::load(const char *vertex_shader_path, const char *fragment_shader_path) {
    Shader s;

    std::string vertex_shader_code = readFile(vertex_shader_path);
    std::string fragment_shader_code = readFile(fragment_shader_path);

    vertex_shader_code = loadFilePreprocess(vertex_shader_code, vertex_shader_path);
    fragment_shader_code = loadFilePreprocess(fragment_shader_code, fragment_shader_path);

    // Preprocessing
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

void Shader::use() const {
    glUseProgram(m_program);
}
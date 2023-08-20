//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_SHADER_H
#define GL_PBR_TRAINING_SHADER_H

#include <GL/glew.h>

#include <string>
#include <boost/filesystem.hpp>

class Shader {
private:
    GLuint m_program{};

    GLuint m_vertex_shader{};
    GLuint m_fragment_shader{};

    static std::string readFile(const char * path);
    static std::string loadFilePreprocess(const std::string& source, const boost::filesystem::path& filename, int level = 0);

public:
//    static void buildGLIncludes();

    static Shader load(const char *vertex_shader_path, const char *fragment_shader_path);

    GLuint getProgram() const;

    void use() const;
};


#endif //GL_PBR_TRAINING_SHADER_H

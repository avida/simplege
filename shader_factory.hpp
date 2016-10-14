#pragma once

#include <GL/glew.h>

#include "generic/singleton.hpp"

class ShaderFactory : public generic::singleton<ShaderFactory>
{
friend generic::singleton<ShaderFactory>;
public:
    void LoadShaders(const std::string& vert_shader_fname, const std::string& frag_shader_fname);
    void UseShader();
    GLuint GetUniformLocation(const std::string& var_name);
protected:
    void init_instance();
    void AddShader(const std::string& shader_code, GLenum shaderType);
    GLuint m_shader_program;
};
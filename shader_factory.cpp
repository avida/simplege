#include "shader_factory.hpp"
#include "utils/logger.hpp"
#include "utils/utils.hpp"
#include <boost/format.hpp>
#include "generic/make_unique.hpp"

void ShaderFactory::LoadShaders(const std::string& vert_shader_fname, 
                               const std::string& frag_shader_fname)
{
    auto shader = utils::LoadFile(vert_shader_fname);
    AddShader(shader, GL_VERTEX_SHADER);
    shader = utils::LoadFile(frag_shader_fname);
    AddShader(shader, GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(m_shader_program);
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &Success);
    if (!Success) 
    {
        glGetProgramInfoLog(m_shader_program, sizeof(ErrorLog), NULL, ErrorLog);
        gl::LogFatal(boost::format("Error linking shader program: %1%") % ErrorLog ); 
    }

    glValidateProgram(m_shader_program);
    glGetProgramiv(m_shader_program, GL_VALIDATE_STATUS, &Success);
    if (!Success) 
    {
        glGetProgramInfoLog(m_shader_program, sizeof(ErrorLog), NULL, ErrorLog);
        gl::LogFatal(boost::format("Invalid shader program: %1%") % ErrorLog );
    }
    m_lighting = gl::make_unique<Lighting>();
}

GLuint ShaderFactory::GetUniformLocation(const std::string& var_name)
{
    auto uniformLocation = glGetUniformLocation(m_shader_program, var_name.c_str());
    if (uniformLocation == 0xFFFFFFFF)
    {
        gl::LogFatal(boost::format("Cannot bind %1% variable") % var_name);
    }
    return uniformLocation;
}

void ShaderFactory::UseShader()
{
    glUseProgram(m_shader_program);
}

void ShaderFactory::AddShader(const std::string& shader_code, GLenum shaderType)
{
    auto shaderObj = glCreateShader(shaderType);
    if (!shaderObj)
    {
        gl::LogFatal("Failed to create shader");
    }
    GLint length = shader_code.length();
    const GLchar* p[1];
    p[0] = shader_code.c_str();
    glShaderSource(shaderObj, 1, p, &length);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
        gl::LogFatal(boost::format("Error compiling shader type %1%: %2%") % shaderType % InfoLog);
    }
    glAttachShader(m_shader_program, shaderObj);
}

void ShaderFactory::init_instance()
{
    m_shader_program = glCreateProgram();
    if (!m_shader_program)
    {
        gl::LogFatal("Error creating shader program");
    }
}
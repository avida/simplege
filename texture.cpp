#include "texture.hpp"
#include "shader_factory.hpp"

Texture::Texture()
{}

void Texture::Load(const std::string path)
{
   m_png.Load(path);
   glGenTextures(1, &m_texture);
   glBindTexture(GL_TEXTURE_2D, m_texture);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_png.GetWidth(), m_png.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_png.GetData());
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   auto& shader_fact = ShaderFactory::get_instance();
   m_sampler = shader_fact.GetUniformLocation("gSampler");
}  

void Texture::init_instance()
{

}

void Texture::Bind()
{
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, m_texture);
   glUniform1i(m_sampler, 0);

}
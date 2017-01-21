#pragma once

#include "libpng.hpp"
#include "generic/singleton.hpp"
#include <GL/glew.h>

class Texture : public generic::singleton<Texture>
{
friend generic::singleton<Texture>;
public:
   Texture();
   void Load(const std::string path);

   void Bind();
protected:
   void init_instance();
   LibPng m_png;
   GLuint m_texture;
   GLuint m_sampler;
};
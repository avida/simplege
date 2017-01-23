#pragma once

#include "libpng.hpp"
#include <GL/glew.h>
#include <boost/shared_ptr.hpp>

class Texture
{
public:
   Texture();
   void Load(const std::string path);

   void Bind();
protected:
   LibPng m_png;
   GLuint m_texture;
   GLuint m_sampler;
};

typedef boost::shared_ptr<Texture> TexturePtr;
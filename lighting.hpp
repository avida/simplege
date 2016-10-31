#pragma once

#include <gmtl/gmtl.h>
#include <GL/glew.h>
#include <memory>

class Lighting
{
public:
Lighting();

void SetAmbientColor(float r, float g, float b);
void SetAmbientIntensity(float intens) { m_ambint_intens = intens; }

void SetDirection(float x, float y, float z);
void SetDiffuseIntensity(float intens) { m_diffuse_intens = intens; }

void ApplyLight();
protected: 
gmtl::Vec3f m_ambient_color;
float m_ambint_intens;

struct {
    GLuint color;
    GLuint ambientIntensity;
    GLuint diffuseIntensity;
    GLuint direction;
} m_lighting;

gmtl::Vec3f m_diffuse_direction;
float m_diffuse_intens;
};

typedef std::unique_ptr<Lighting> LightingPtr;
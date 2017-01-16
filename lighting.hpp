#pragma once

#include <math_3d.hpp>
#include <memory>
#include <GL/glew.h>

class Lighting
{
public:
Lighting();

void SetAmbientIntensity(float intens) { m_ambint_intens = intens; }

void SetDirection(float x, float y, float z);
void SetDiffuseIntensity(float intens) { m_diffuse_intens = intens; }

void ApplyLight(const Vector3f& material_color);
protected:
float m_ambint_intens;

struct {
    GLuint color;
    GLuint ambientIntensity;
    GLuint diffuseIntensity;
    GLuint direction;
} m_lighting;

Vector3f m_diffuse_direction;
float m_diffuse_intens;
};

typedef std::unique_ptr<Lighting> LightingPtr;
#pragma once

#include <math_3d.hpp>
#include <memory>
#include <GL/glew.h>

const int kMaxSpitLight = 5;

class Lighting
{
public:
Lighting();

void SetAmbientIntensity(float intens) { m_ambint_intens = intens; }

void SetDirection(float x, float y, float z);
void SetDiffuseIntensity(float intens) { m_diffuse_intens = intens; }

void ApplyLight(const Vector3f& material_color);
protected:

struct Light
{
    GLuint glColor;
    GLuint glDiffuseIntensity;
    GLuint glAmbientIntensity;

    Vector3f color;
    float diffuse_intens;
    float ambient_intens;
};

struct PointLightAttenuation
{
   GLuint glConstant;
   GLuint glLinear;
   GLuint glExp;

   float constant;
   float linear;
   float exp;
};

struct DirectionalLight
{
   Light glLight;
   GLuint glDirection;
   Vector3f direction;
};

struct PointLight
{
   Light glLight;
   GLuint glPosition;
   Vector3f position;
}

DirectionalLight directional_light;
PointLightAttenuation light_attenuation;
std::vector<PointLight> point_lights;

};

typedef std::unique_ptr<Lighting> LightingPtr;
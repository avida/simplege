#pragma once

#include <math_3d.hpp>
#include <memory>
#include <vector>
#include <GL/glew.h>

const int kMaxSpitLight = 5;

class Lighting
{
public:

struct Light
{
    GLuint glColor;
    GLuint glDiffuseIntensity;
    GLuint glAmbientIntensity;

    Vector3f color;
    float diffuseIntensity;
    float ambientIntensity;
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
   Light light;
   GLuint glDirection;
   Vector3f direction;
};

struct PointLight
{
   Light glLight;
   GLuint glPosition;
   Vector3f position;
};

struct SpecularLight
{
   GLuint glIntensity;
   GLuint glPower;
   float intensity;
   float power;
};

Lighting();

void SetDirectionalAmbientIntensity(float intens) { directional_light.light.ambientIntensity = intens; }
void SetDirectionalDiffuseIntensity(float intens) { directional_light.light.diffuseIntensity = intens; }
void SetDirection(float x, float y, float z);

void ApplyLight(const Vector3f& material_color);
protected:

DirectionalLight directional_light;
SpecularLight specular_light;
PointLightAttenuation light_attenuation;
std::vector<PointLight> point_lights;
GLuint glCameraPos;

};

typedef std::unique_ptr<Lighting> LightingPtr;
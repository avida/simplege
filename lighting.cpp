#include "lighting.hpp"
#include "shader_factory.hpp"

template <class T> 
void FillVector(T& vec, float x, float y, float z)
{
	vec.x = x;
	vec.y = y;
	vec.z = z;
}

Lighting::Lighting()
{
    auto& shader_fact = ShaderFactory::get_instance();
    m_lighting.color = shader_fact.GetUniformLocation("gDirectionalLight.Color");
    m_lighting.direction = shader_fact.GetUniformLocation("gDirectionalLight.Direction");
    m_lighting.diffuseIntensity = shader_fact.GetUniformLocation("gDirectionalLight.DiffuseIntensity");
    m_lighting.ambientIntensity = shader_fact.GetUniformLocation("gDirectionalLight.AmbientIntensity");
}

void Lighting::SetAmbientColor(float x, float y, float z)
{
	FillVector(m_ambient_color, x, y, z);
}

void Lighting::SetDirection(float x, float y, float z)
{
	FillVector(m_diffuse_direction, x, y, z);
  m_diffuse_direction.Normalize();
}

void Lighting::ApplyLight()
{
   glUniform3f(m_lighting.direction, m_diffuse_direction.x, m_diffuse_direction.y, m_diffuse_direction.z);
   glUniform1f(m_lighting.ambientIntensity, m_ambint_intens);
   glUniform3f(m_lighting.color, m_ambient_color.x, m_ambient_color.y, m_ambient_color.z);
   glUniform1f(m_lighting.diffuseIntensity, m_diffuse_intens);
}
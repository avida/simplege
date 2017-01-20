#include "lighting.hpp"
#include "shader_factory.hpp"
#include "camera.hpp"

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

    m_specular_light.cameraPos = shader_fact.GetUniformLocation("gSpecularLight.cameraPos");
    m_specular_light.power = shader_fact.GetUniformLocation("gSpecularLight.SpecularPower");
    m_specular_light.intensity = shader_fact.GetUniformLocation("gSpecularLight.SpecularIntensity");
}

void Lighting::SetDirection(float x, float y, float z)
{
	FillVector(m_diffuse_direction, x, y, z);
  m_diffuse_direction.Normalize();
}

void Lighting::ApplyLight(const Vector3f& material_color)
{
   glUniform3f(m_lighting.direction, m_diffuse_direction.x, m_diffuse_direction.y, m_diffuse_direction.z);
   glUniform1f(m_lighting.ambientIntensity, m_ambint_intens);
   glUniform3f(m_lighting.color, material_color.x, material_color.y, material_color.z);
   glUniform1f(m_lighting.diffuseIntensity, m_diffuse_intens);

  glUniform1f(m_specular_light.power, 8);
  glUniform1f(m_specular_light.intensity, 2);
  auto camera_pos = Camera::GetGlobalCamera().GetPosition();
  glUniform3f(m_specular_light.cameraPos, camera_pos.x, camera_pos.y, camera_pos.z);
}
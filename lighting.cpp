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

   directional_light.glDirection =
      shader_fact.GetUniformLocation("gDirectionalLight.direction");
   directional_light.light.glDiffuseIntensity = 
      shader_fact.GetUniformLocation("gDirectionalLight.light.diffuseIntensity");
   directional_light.light.glAmbientIntensity = 
      shader_fact.GetUniformLocation("gDirectionalLight.light.ambientIntensity");
   directional_light.light.glColor =
      shader_fact.GetUniformLocation("gDirectionalLight.light.color");

   glCameraPos = shader_fact.GetUniformLocation("cameraPos");

   specular_light.glPower = shader_fact.GetUniformLocation("gSpecularLight.power");
   specular_light.glIntensity = shader_fact.GetUniformLocation("gSpecularLight.intensity");

   light_attenuation.glConstant = shader_fact.GetUniformLocation("gPointLightAttenuation.Constant");
   light_attenuation.glLinear = shader_fact.GetUniformLocation("gPointLightAttenuation.Linear");
   light_attenuation.glExp = shader_fact.GetUniformLocation("gPointLightAttenuation.Exp");
}

void Lighting::SetPointLightAttenuation(float constant, float linear, float exp)
{
  light_attenuation.constant = constant;
  light_attenuation.linear = linear;
  light_attenuation.exp = exp;
}

void Lighting::SetDirection(float x, float y, float z)
{
	FillVector(directional_light.direction, x, y, z);
  directional_light.direction.Normalize();
}

void Lighting::ApplyLight(const Vector3f& material_color)
{
   glUniform3f(directional_light.glDirection, directional_light.direction.x, 
                                              directional_light.direction.y,
                                              directional_light.direction.z);
   glUniform1f(directional_light.light.glAmbientIntensity, 
                                              directional_light.light.ambientIntensity);
   glUniform1f(directional_light.light.glDiffuseIntensity, 
                                              directional_light.light.diffuseIntensity);
   
   glUniform3f(directional_light.light.glColor, material_color.x, material_color.y, material_color.z);

  glUniform1f(specular_light.glPower, 16);
  glUniform1f(specular_light.glIntensity, 2);
  auto camera_pos = Camera::GetGlobalCamera().GetPosition();
  glUniform3f(glCameraPos, camera_pos.x, camera_pos.y, camera_pos.z);
}
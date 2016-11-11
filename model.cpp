#include "model.hpp"
#include "shader_factory.hpp"
#include "camera.hpp"

Model::Model()
{
   auto& shader_fact = ShaderFactory::get_instance();
   m_gWVP = shader_fact.GetUniformLocation("WVP");
   m_gWorld = shader_fact.GetUniformLocation("gWorld");
}

void Model::SetPosition(float x, float y, float z)
{
   m_trans.x = x;
   m_trans.y = y;
   m_trans.z = z;
}

const Vector3f& Model::GetPosition()
{
   return m_trans;
}

void Model::SetScale(float scale_x, float scale_y, float scale_z)
{
   m_scale.x = scale_x;
   m_scale.y = scale_y;
   m_scale.z = scale_z;
}

const Vector3f& Model::GetScale()
{
   return m_scale;
}

const Vector3f& Model::GetRotation()
{
   return m_rot;
}

void Model::SetRotation(float rot_x, float rot_y, float rot_z)
{
   m_rot.x = rot_x;
   m_rot.y = rot_y;
   m_rot.z = rot_z;
}

void Model::Render()
{
   auto& camera = Camera::GetGlobalCamera();
   auto& shader_fact = ShaderFactory::get_instance();

   Matrix4f rotate;
   rotate.InitRotateTransform(m_rot);
   Matrix4f scale;
   scale.InitScaleTransform(m_scale);
   Matrix4f translate;
   translate.InitTranslationTransform(m_trans);
   auto m = translate *  rotate * scale;
   auto mvp = camera.GetProjectionMatrix() *  m;
   glUniformMatrix4fv(m_gWorld, 1, GL_TRUE, &m .m[0][0]);
   glUniformMatrix4fv(m_gWVP, 1, GL_TRUE, &mvp.m[0][0]);
   shader_fact.GetLightingModel().ApplyLight();

   shader_fact.UseShader();
}
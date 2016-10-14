#include "model.hpp"
#include "shader_factory.hpp"
#include "camera.hpp"

Model::Model()
{
   auto& shader_fact = ShaderFactory::get_instance();
   m_gWVP = shader_fact.GetUniformLocation("WVP");
}

void Model::SetPosition(float x, float y, float z)
{
   m_trans[0] = x;
   m_trans[1] = y;
   m_trans[2] = z;
}

gmtl::Vec3f Model::GetPosition()
{
   return m_trans;
}

void Model::SetScale(float scale_x, float scale_y, float scale_z)
{
   m_scale[0] = scale_x;
   m_scale[1] = scale_y;
   m_scale[2] = scale_z;
   // gmtl::setScale(m_trans_matrix, vec);  
}

gmtl::Vec3f Model::GetScale()
{
   return m_scale;
}

gmtl::EulerAngleXYZf Model::GetRotation()
{
   return m_rot;
}

void Model::SetRotation(float rot_x, float rot_y, float rot_z)
{
   m_rot[0] = rot_x;
   m_rot[1] = rot_y;
   m_rot[2] = rot_z;
}

void Model::Render()
{
   auto& camera = Camera::GetGlobalCamera();
   auto& shader_fact = ShaderFactory::get_instance();
   auto m = gmtl::makeRot< gmtl::Matrix44f > (m_rot);
   gmtl::setTrans(m, m_trans);
   m *= gmtl::makeScale<gmtl::Matrix44f>(m_scale);
   m = camera.GetProjectionMatrix() * m;
   glUniformMatrix4fv(m_gWVP, 1, GL_TRUE, &m[0][0]);
   shader_fact.UseShader();
}
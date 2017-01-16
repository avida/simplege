#include "camera.hpp"
#include "utils/logger.hpp"

Camera Camera::m_global_camera;

Camera::Camera()
{
   SetPosition(0, 0, 10);
   SetRotation(0, 90);
}

void Camera::SetPosition(float x, float y, float z) 
{
   m_pos.x = x;
   m_pos.y = y;
   m_pos.z = z;
   m_translation_matrix.InitTranslationTransform(-m_pos.x, -m_pos.y, -m_pos.z);
};

void Camera::SetRotation(float angleV, float angleH)
{ 
   m_angleV = angleV; 
   m_angleH = angleH;
   Update();
}

void Camera::Update()
{
    static const Vector3f Vaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(m_angleH, Vaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
    View.Rotate(m_angleV, Haxis);
    View.Normalize();

    m_target = View;
    m_target.Normalize();

    m_up = m_target.Cross(Haxis);
    m_up.Normalize();
}
// Projection
void Camera::SetProjectionParameters(float angle, float width,  float height, float nearZ, float farZ)
{
   PersProjInfo projection_info;
   projection_info.FOV = angle;
   projection_info.Width = width;
   projection_info.Height = height;
   projection_info.zNear = nearZ;
   projection_info.zFar = farZ;
   m_projection_matrix.InitPersProjTransform(projection_info);
}

void Camera::SetViewAngle(float angle)
{

};

void Camera::SetSize(float w, float h)
{

};

void Camera::SetPlanes(float nearZ, float farZ)
{
};

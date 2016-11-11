#include "camera.hpp"
#include "utils/logger.hpp"

Camera Camera::m_global_camera;

Camera::Camera()
{
}
void Camera::SetPosition(float x, float y, float z) {};

void Camera::SetUp(float x, float y, float z) {};

void Camera::SetDirection(float x, float y, float z){};

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

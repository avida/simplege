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
   auto ar = width / height;
   auto tanA = tanf(angle/2);
   gl::Log(ar);
   gl::Log((float)tanA);
   m_projection_matrix[0][0] = 1 / (tanA * ar);
   m_projection_matrix[1][1] = 1 / tanA;
   m_projection_matrix[2][2] = (-nearZ - farZ) / (nearZ - farZ);
   m_projection_matrix[2][3] = 2 * farZ * nearZ / (nearZ - farZ);
   m_projection_matrix[3][2] = 1;
   m_projection_matrix[3][3] = 0;
   gl::Log(2 * farZ * nearZ / (nearZ - farZ));
   gl::Log(m_projection_matrix);
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

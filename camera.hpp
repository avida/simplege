#pragma once
#include "math_3d.hpp"

class Camera
{
   public:
      Camera();
   public:
      void SetPosition(float x, float y, float z);
      void SetUp(float x, float y, float z);
      void SetDirection(float x, float y, float z);
      // Projection
      void SetProjectionParameters(float angle, float height,  float width, float nearZ, float farZ);
      const Matrix4f& GetProjectionMatrix() { return m_projection_matrix; };
      void SetViewAngle(float angle);
      void SetSize(float w, float h);
      void SetPlanes(float nearZ, float farZ);
      static Camera& GetGlobalCamera() {return m_global_camera; }
   private:
      Matrix4f m_projection_matrix;
      static Camera m_global_camera;
};
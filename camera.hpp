#pragma once
#include "math_3d.hpp"

class Camera
{
   public:
      Camera();
   public:
      void SetPosition(float x, float y, float z);
      void SetPosition(Vector3f pos) { m_pos = pos; m_translation_matrix.InitTranslationTransform(-m_pos.x, -m_pos.y, -m_pos.z);}
      void SetRotation(float angleV, float angleF);
      const Vector3f& GetUp() { return m_up; }
      const Vector3f& GetTarget() { return m_target; }
      const Vector3f& GetPosition() { return m_pos; }

      // Projection
      void SetProjectionParameters(float angle, float height,  float width, float nearZ, float farZ);
      const Matrix4f& GetProjectionMatrix() { return m_projection_matrix; }
      const Matrix4f& GetTranslationMatrix() { return m_translation_matrix; }
      void SetViewAngle(float angle);
      void SetSize(float w, float h);
      void SetPlanes(float nearZ, float farZ);
      static Camera& GetGlobalCamera() {return m_global_camera; }

      void Update();
   private:
      float m_angleV;
      float m_angleH;
      Vector3f m_pos;
      Vector3f m_up;
      Vector3f m_target;
      Matrix4f m_projection_matrix;
      Matrix4f m_translation_matrix;
      static Camera m_global_camera;
};
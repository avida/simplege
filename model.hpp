#pragma once

#include <GL/glew.h>
#include <boost/shared_ptr.hpp>
#include "utils/logger.hpp"
#include "math_3d.hpp"
#include "texture.hpp"

class Model
{
public:
    Model();
    ~Model() { gl::Log("erased");};
    void SetPosition(float x, float y, float z);
    const Vector3f& GetPosition();

    void SetScale(float scale_x, float scale_y, float scale_z);
    const Vector3f& GetScale();

    void SetRotation(float rot_x, float rot_y, float rot_z);
    const Vector3f& GetRotation();
    void Render();
    void SetColorF(float r, float g, float b);
    void SetColor(int r, int g, int b);
protected:
    GLuint m_gWVP;
    GLuint m_gWorld;
    Vector3f m_scale;
    Vector3f m_trans;
    Vector3f m_rot;

    Vector3f m_color;
};

typedef boost::shared_ptr<Model> ModelPtr; 
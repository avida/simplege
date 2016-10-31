#pragma once 

#include <gmtl/gmtl.h>
#include <GL/glew.h>
#include <boost/shared_ptr.hpp>
#include "utils/logger.hpp"

class Model
{
public:
    Model();
    ~Model() { gl::Log("erased");};
    void SetPosition(float x, float y, float z);
    gmtl::Vec3f GetPosition();

    void SetScale(float scale_x, float scale_y, float scale_z);
    gmtl::Vec3f GetScale();

    void SetRotation(float rot_x, float rot_y, float rot_z);
    gmtl::EulerAngleXYZf GetRotation();
    void Render();
protected:
    GLuint m_gWVP;
    GLuint m_gWorld;
    gmtl::Vec3f m_scale = {1, 1, 1};
    gmtl::Vec3f m_trans;
    gmtl::EulerAngleXYZf m_rot;
};

typedef boost::shared_ptr<Model> ModelPtr; 
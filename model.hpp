#pragma once 

#include <boost/shared_ptr.hpp>

class Model
{
public:
    Model();
    void SetPosition(int x, int y, int z);
    void SetScale(float scale);
    void SetRotation(float rot_x, float rot_y, float rot_z);
    void Render();
protected:

};

typedef boost::shared_ptr<Model> ModelPtr; 
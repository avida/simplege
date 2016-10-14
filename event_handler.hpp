#pragma once
#include "i_handler.hpp"

#include "model_factory_manager.hpp"

class EventHandler: public IHandler 
{
public:
    EventHandler();
    void OnRender();
    void OnKeyboard(unsigned char key, int x, int y);
private:
   ModelPtr m_model;
   float angle = .0f;
   float angle_z = .0f;

};
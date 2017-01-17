#pragma once
#include "i_handler.hpp"
#include "camera.hpp"

#include "model_factory_manager.hpp"

class EventHandler: public IHandler 
{
public:
    EventHandler();
    void OnRender();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnMouseMove(int x, int y);
    void OnMouseButton(int button, int state, int x, int y);
private:
   float angle = .0f;
   float angle_z = .0f;
   bool m_pressed;
   Camera& m_camera;
   Vector2i m_prev_mouse_pos;
};
#pragma once
#include "i_handler.hpp"

class EventHandler: public IHandler 
{
public:
    EventHandler(){}
    void OnRender();
    void OnKeyboard(unsigned char key, int x, int y);
};
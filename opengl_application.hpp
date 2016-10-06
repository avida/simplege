#pragma once
#include "i_handler.hpp"

#include <string> 


class Application
{
public:
    Application(int & argc, char ** argv);
    void CreateGLWindow(int h, int w, const std::string& title);
    void SetHandler(IHandlerPtr handler) { m_handler = handler; }
    void Run();
private:
    void InitHandler();
    static void Render();
    static void KeyboardCB(unsigned char Key, int x, int y);
    static IHandlerPtr m_handler;    
};

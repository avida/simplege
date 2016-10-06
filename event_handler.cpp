#include "event_handler.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

void EventHandler::OnRender()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void EventHandler::OnKeyboard(unsigned char key, int x, int y)
{
    std::cout << (int) key <<" x:" << x  << " " << y << std::endl;
    switch(key)
    {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

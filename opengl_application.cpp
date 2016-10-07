#include "opengl_application.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

IHandlerPtr Application::m_handler  = IHandlerPtr();

Application::Application(int& argc, char ** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

void Application::CreateGLWindow(int h, int w, const std::string& title)
{
    glutInitWindowSize(h, w);
    glutCreateWindow(title.c_str());
    auto res = glewInit();
    if (res != GLEW_OK)
    {
        std::cout << "Error: " << glewGetErrorString(res) << std::endl;
    }
}

void Application::Render()
{
    m_handler->OnRender();
}

void Application::KeyboardCB(unsigned char Key, int x, int y)
{
        m_handler->OnKeyboard(Key, x, y);
}

void Application::InitHandler()
{
    glutDisplayFunc(Render);
    glutKeyboardFunc(KeyboardCB);
}

void Application::Run()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    InitHandler();
    // Assert(m_handler);
    glutMainLoop();
}
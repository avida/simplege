#include "opengl_application.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "utils/logger.hpp"

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
        gl::LogFatal(boost::format("Error: %1%") % glewGetErrorString(res));
    }
}

void Application::Render()
{
    m_handler->OnRender();
}

void Application::KeyboardCB(unsigned char key, int x, int y)
{
    m_handler->OnKeyboard(key, x, y);
}

void Application::MouseMoveCB(int x, int y)
{
    m_handler->OnMouseMove(x, y);
}

void Application::MouseButtonCB(int button, int state, int x, int y)
{
    m_handler->OnMouseButton(button, state, x, y);   
}

void Application::InitHandler()
{
    glutDisplayFunc(Render);
    glutIdleFunc(Render);
    glutKeyboardFunc(KeyboardCB);
    glutPassiveMotionFunc(MouseMoveCB);
    glutMotionFunc(MouseMoveCB);
    glutMouseFunc(MouseButtonCB);
}

void Application::Run()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    // glCullFace(GL_BACK);
    // glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    InitHandler();
    // Assert(m_handler);
    glutMainLoop();
}
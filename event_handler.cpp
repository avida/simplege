#include "event_handler.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "utils/logger.hpp"
#include "utils/utils.hpp"

#define ROT_STEP 5.f
EventHandler::EventHandler()
{
    m_model = ModelFactoryManager::get_instance().GetFactory("sample")->CreateModel();
    m_model->SetScale(.5f, 1.f,1.f);
    m_model->SetPosition(0.f,1.f,10.f);
}

void EventHandler::OnRender()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    ModelFactoryManager::get_instance().FactoriesRender();
    glutSwapBuffers();
}

void EventHandler::OnKeyboard(unsigned char key, int x, int y)
{
    gl::Log(boost::format("key: %1% x:%2% y: %3%") % (int)key % x % y);
    Vector3f pos = m_model->GetPosition();
    switch(key)
    {
        case 27:
            gl::LogFatal("Esc pressed");
            break;
        case 'a':
        case 'A':
            if (!m_model) break;
            angle += ROT_STEP;
            // pos[0] -= .1f;
            // m_model->SetScale(.5f, 2.f,0);
            break;
        case 'd':
        case 'D':
            if (!m_model) break;
            angle -= ROT_STEP;
            // pos[0] += .1f;
            // m_model->SetScale(.5f, 2.f,0);
            // m_model->SetPosition(-.5f,0.f,0);
            break;
        case 's':
        case 'S':
            pos.y -= .1f;
            angle_z += ROT_STEP;
            break;
        case 'w':
        case 'W':
                angle_z -= ROT_STEP;
                pos.y += .1f;
            break;
        case 'x':
        case 'X':
            break;
        default:
            break;
    }
    m_model->SetPosition(pos.x, pos.y, pos.z);
    m_model->SetRotation(0.f,angle_z, angle);
    gl::Log(boost::format("angle: %1%") % angle);
}
#include "event_handler.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "camera.hpp"
#include "utils/logger.hpp"
#include "utils/utils.hpp"

#define ROT_STEP 5.f
const int kCameraStep = 1;
EventHandler::EventHandler()
{
    m_model = ModelFactoryManager::get_instance().GetFactory("sample")->CreateModel();
    //m_model->SetScale(.5f, 1.f,1.f);
    m_model->SetPosition(0, 0, 2);
    // auto m2 = ModelFactoryManager::get_instance().GetFactory("sample")->CreateModel();
    // m2->SetPosition(5.f,10,15.f);
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
    auto& camera = Camera::GetGlobalCamera();
    auto camera_pos = camera.GetPosition();
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
            pos.z -= .1f;
            angle_z += ROT_STEP;
            break;
        case 'w':
        case 'W':
                angle_z -= ROT_STEP;
                pos.z += .1f;
            break;
        case 'x':
        case 'X':
            break;
        case 'f':
        case 'F':
            camera_pos.x -= kCameraStep;
            break;
        case 'h':
        case 'H':
            camera_pos.x += kCameraStep;
            break;
        case 'g':
        case 'G':
            camera_pos.z -= kCameraStep;
            break;
        case 't':
        case 'T':
            camera_pos.z += kCameraStep;
            break;
        default:
            break;
    }
    m_model->SetPosition(pos.x, pos.y, pos.z);
    m_model->SetRotation(0.f,angle_z, angle);
    camera.SetPosition(camera_pos);
    gl::Log(boost::format("pos: %1% %2% %3% \n camera_pos: %4% %5% %6%") % pos.x % pos.y % pos.z % camera_pos.x % camera_pos.y % camera_pos.z);
}
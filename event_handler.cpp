#include "event_handler.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "utils/logger.hpp"
#include "utils/utils.hpp"

#define ROT_STEP 5.f
#define CAMERA_ROT_STEP 0.1f
const int kCameraStep = 1;

EventHandler::EventHandler():m_camera(Camera::GetGlobalCamera()), m_pressed(false)
{
    m_model = ModelFactoryManager::get_instance().GetFactory("sample")->CreateModel();
    m_model->SetScale(.5f, 1.f,1.f);
    m_model->SetPosition(0, 0, 0);
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

void EventHandler::OnMouseButton(int button, int state, int x, int y)
{
    // gl::Log(boost::format("mousebtn %1%, state %2%: x: %3% y:%4%") % button % state % x % y);
    m_pressed = state==0;
}

void EventHandler::OnMouseMove(int x, int y)
{
    auto new_pos = Vector2i(x, y);
    auto delta = m_prev_mouse_pos - new_pos;
    m_prev_mouse_pos = new_pos;
    if (!m_pressed) return;
    auto h_angle = m_camera.GetHAngle();
    auto v_angle = m_camera.GetVAngle();
    // gl::Log(boost::format("mouse: dx: %1% dy:%2%") % delta.x % delta.y);

    m_camera.SetRotation(v_angle - CAMERA_ROT_STEP * delta.y,
                         h_angle - CAMERA_ROT_STEP * delta.x);
    h_angle = m_camera.GetHAngle();
    v_angle = m_camera.GetVAngle();
    // gl::Log(boost::format("rotation v: %1% h:%2%") % v_angle % h_angle);
}

void EventHandler::OnKeyboard(unsigned char key, int x, int y)
{
    gl::Log(boost::format("key: %1% x:%2% y: %3%") % (int)key % x % y);
    Vector3f pos = m_model->GetPosition();
    auto camera_pos = m_camera.GetPosition();
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
            camera_pos.x += kCameraStep;
            break;
        case 'h':
        case 'H':
            camera_pos.x -= kCameraStep;
            break;
        case 'g':
        case 'G':
            camera_pos.y -= kCameraStep;
            break;
        case 't':
        case 'T':
            camera_pos.y += kCameraStep;
            break;
        case 'u':
        case 'U':
            camera_pos.z -= kCameraStep;
            break;
        case 'j':
        case 'J':
            camera_pos.z += kCameraStep;
            break;
        default:
            break;
    }
    m_model->SetPosition(pos.x, pos.y, pos.z);
    m_model->SetRotation(0.f,angle_z, angle);
    m_camera.SetPosition(camera_pos);
    gl::Log(boost::format("pos: %1% %2% %3% \n camera_pos: %4% %5% %6%") % pos.x % pos.y % pos.z % camera_pos.x % camera_pos.y % camera_pos.z);
}
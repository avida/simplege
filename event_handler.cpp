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
{}

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
    // gl::Log(boost::format("key: %1% x:%2% y: %3%") % (int)key % x % y);
    auto camera_pos = m_camera.GetPosition();
    const auto& camera_target = m_camera.GetTarget();
    const auto& camera_up = m_camera.GetUp();
    switch(key)
    {
        case 27:
            gl::LogFatal("Esc pressed");
            break;
        case 'a':
        case 'A':
            camera_pos += camera_target.Cross(camera_up);
            break;
        case 'd':
        case 'D':
            camera_pos -= camera_target.Cross(camera_up);
            break;
        case 's':
        case 'S':
            camera_pos -= camera_target;
            break;
        case 'w':
        case 'W':
                camera_pos += camera_target;
            break;
        case 'q':
        case 'Q':
            gl::LogFatal("Bye Bye");
            break;
        default:
            break;
    }
    m_camera.SetPosition(camera_pos);
    gl::Log(boost::format("camera_pos: %1% %2% %3%") % camera_pos.x % camera_pos.y % camera_pos.z);
}
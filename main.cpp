#include <iostream>
#include <string>
#include <cstdio>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "camera.hpp"
#include "opengl_application.hpp"
#include "event_handler.hpp"
#include "model_factory_manager.hpp"
#include "shader_factory.hpp"

#include "utils/utils.hpp"
#include "utils/logger.hpp"


const int WINDOW_HEIGHT = 320;
const int WINDOW_WIDTH = 640;

const std::string vertexShaderFilePath = "../shaders/shader.vs";
const std::string fragmentShaderFilePath = "../shaders/shader.fs";

int main(int argc, char** argv)
{
    Application app(argc, argv);
    app.CreateGLWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "simplegl");
    auto& shader_fact = ShaderFactory::get_instance();
    shader_fact.LoadShaders(vertexShaderFilePath, fragmentShaderFilePath);

    auto& camera = Camera::GetGlobalCamera();
    camera.SetProjectionParameters(30.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1, 100);
    auto factory = ModelFactoryManager::get_instance().SetupFactory("sample", "model.obj");
    auto plane_factory = ModelFactoryManager::get_instance().SetupFactory("plane", "plane.obj");
    auto sky_factory = ModelFactoryManager::get_instance().SetupFactory("sky", "sky.obj");

    auto handler = boost::make_shared<EventHandler>();
    app.SetHandler(handler);
    for (double x = 0; x < 5; x++)
    {
        auto model_x = factory->CreateModel();
        model_x->SetPosition(x, 0, 0);
        model_x->SetColorF(x/10, 0, 0); //red
        auto model_y = factory->CreateModel();
        model_y->SetPosition(0, x, 0);
        model_y->SetColorF(0, x/10, 0);// green
        auto model_z = factory->CreateModel();
        model_z->SetPosition(0, 0, x);
        model_z->SetColorF(0, 0, x/10); //blue
    }
    auto plane = plane_factory->CreateModel();
    plane->SetPosition(0,-1,0);
    plane->SetScale(10,10,10);
    plane->SetColor(220, 220, 31);
    auto sky = sky_factory->CreateModel();
    sky->SetColor(80, 194, 206);
    //Lighting
    auto& lighting = shader_fact.GetLightingModel();
    lighting.SetAmbientIntensity(0.1);
    lighting.SetDiffuseIntensity(1);
    lighting.SetDirection(1, -0.5, -1);
    try
    {
        app.Run();
    }
    catch(const std::runtime_error&)
    {
        gl::Log("Exception catched");
    }
    gl::Log("Bye");
    return 0;
}
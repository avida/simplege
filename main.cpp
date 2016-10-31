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

const int WINDOW_HEIGHT = 200;
const int WINDOW_WIDTH = 300;

const std::string vertexShaderFilePath = "../shaders/shader.vs";
const std::string fragmentShaderFilePath = "../shaders/shader.fs";

int main(int argc, char** argv)
{
    gl::Log("Hello");
    Application app(argc, argv);
    app.CreateGLWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cool app");
    auto& shader_fact = ShaderFactory::get_instance();
    shader_fact.LoadShaders(vertexShaderFilePath, fragmentShaderFilePath);

    auto& camera = Camera::GetGlobalCamera();
    camera.SetProjectionParameters(gmtl::Math::deg2Rad(30.0f), WINDOW_WIDTH, WINDOW_HEIGHT, 1, 100);

    auto factory = ModelFactoryManager::get_instance().SetupFactory("sample", "model.obj");
    auto handler = boost::make_shared<EventHandler>();
    app.SetHandler(handler);

    auto model = factory->CreateModel();
    model->SetPosition(0, 0, 15);
    //Lighting
    auto& lighting = shader_fact.GetLightingModel();
    lighting.SetAmbientColor(0.1, 1, 1);
    lighting.SetAmbientIntensity(.0);
    lighting.SetDiffuseIntensity(.8);
    lighting.SetDirection(1, 0, 0);
    app.Run();
    gl::Log("Bye");
    return 0;
}
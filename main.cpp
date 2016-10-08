#include <iostream>
#include <string>

#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "opengl_application.hpp"
#include "event_handler.hpp"
#include "model_factory.hpp"
#include "shader_factory.hpp"

#include "utils/utils.hpp"

const int WINDOW_HEIGHT = 200;
const int WINDOW_WIDTH = 300;

const std::string vertexShaderFilePath = "../shaders/shader.vs";
const std::string fragmentShaderFilePath = "../shaders/shader.fs";

using namespace std;

int main(int argc, char** argv)
{
    cout <<"Hello" << endl;
    Application app(argc, argv);
    app.CreateGLWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cool app");
    auto handler = boost::make_shared<EventHandler>();
    app.SetHandler(handler);
    auto& shader_fact = ShaderFactory::get_instance();
    shader_fact.LoadShaders(vertexShaderFilePath, fragmentShaderFilePath);
    app.Run();
    cout <<"Bye" << endl;
    return 0;
}
#include <iostream>
#include <string>

#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "opengl_application.hpp"
#include "event_handler.hpp"

const int WINDOW_HEIGHT = 200;
const int WINDOW_WIDTH = 300;

using namespace std;

int main(int argc, char** argv)
{
    cout <<"Hello" << endl;
    Application app(argc, argv);
    app.CreateGLWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cool app");
    auto handler = boost::make_shared<EventHandler>();
    app.SetHandler(handler);
    app.Run();
    
    cout <<"Bye" << endl;
    return 0;
}
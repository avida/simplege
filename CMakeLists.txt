cmake_minimum_required(VERSION 3.7)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x" )
include_directories("G:/libs/glew-1.10.0/include", "G:/libs/freeglut/include", "g:/libs/boost_1_62_0")
link_directories("G:/libs/freeglut/lib", "G:/libs/glew-1.10.0/lib")
add_executable(MyEngine main.cpp opengl_application.cpp event_handler.cpp)
target_link_libraries(MyEngine freeglut glew32 opengl32)


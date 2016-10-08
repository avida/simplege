cmake_minimum_required(VERSION 3.7)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x" )

include_directories(".",
                    "G:/libs/glew-1.10.0/include", 
                    "G:/libs/freeglut/include", 
                    "g:/libs/boost_1_62_0",
                    "G:/libs/gmtl")

link_directories("G:/libs/freeglut/lib",
                 "G:/libs/glew-1.10.0/lib",
                 "g:/libs/boost_1_62_0/bin.v2/libs/system/build/gcc-mingw-5.3.0/release/link-static/threading-multi/",
                 "g:/libs/boost_1_62_0/bin.v2/libs/filesystem/build/gcc-mingw-5.3.0/release/link-static/threading-multi/")

add_executable(MyEngine 
                        main.cpp 
                        opengl_application.cpp 
                        event_handler.cpp 
                        model_factory.cpp
                        shader_factory.cpp
                        utils/utils.cpp)

target_link_libraries(MyEngine freeglut glew32 opengl32 boost_system-mgw53-mt-1_62 boost_filesystem-mgw53-mt-1_62)
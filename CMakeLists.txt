cmake_minimum_required(VERSION 3.7)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(".",
                    "./3rdParty/gmtl",
                    "G:/libs/glew-1.10.0/include", 
                    "G:/libs/freeglut/include", 
                    "g:/libs/boost_1_62_0",
                    "G:/libs/gmtl",
                    "g:/libs/assimp-3.1.1/include")

link_directories("G:/libs/freeglut/lib",
                 "G:/libs/glew-1.10.0/lib",
                 "g:/libs/boost_1_62_0/bin.v2/libs/system/build/gcc-mingw-5.3.0/release/link-static/threading-multi/",
                 "g:/libs/boost_1_62_0/bin.v2/libs/filesystem/build/gcc-mingw-5.3.0/release/link-static/threading-multi/",
                 "g:/libs/assimp-3.1.1/build/code")

add_executable(MyEngine 
                        main.cpp 
                        opengl_application.cpp 
                        event_handler.cpp 
                        model_factory.cpp
                        model_factory_manager.cpp
                        shader_factory.cpp
                        utils/utils.cpp
                        model.cpp
                        camera.cpp)

target_link_libraries(MyEngine freeglut glew32 opengl32 boost_system-mgw53-mt-1_62 boost_filesystem-mgw53-mt-1_62 assimp zlibstatic)
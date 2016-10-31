cmake_minimum_required(VERSION 3.7)
set (LIBS_DIR e:/libs)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(".",
                    "./3rdParty/gmtl",
                    "${LIBS_DIR}/glew/include", 
                    "${LIBS_DIR}/freeglut/include", 
                    "${LIBS_DIR}/boost_1_62_0",
                    "${LIBS_DIR}/gmtl",
                    "${LIBS_DIR}/assimp/include")

link_directories("${LIBS_DIR}/freeglut/src",
                 "${LIBS_DIR}/glew/lib",
                 "${LIBS_DIR}/boost_1_62_0/bin.v2/libs/system/build/gcc-mingw-6.2.0/release/link-static/threading-multi/",
                 "${LIBS_DIR}/boost_1_62_0/bin.v2/libs/filesystem/build/gcc-mingw-6.2.0/release/link-static/threading-multi/",
                 "${LIBS_DIR}/assimp/build/code",
                 "${LIBS_DIR}/png")

add_executable(MyEngine 
                        main.cpp 
                        opengl_application.cpp 
                        event_handler.cpp 
                        model_factory.cpp
                        model_factory_manager.cpp
                        shader_factory.cpp
                        utils/utils.cpp
                        model.cpp
                        camera.cpp
                        lighting.cpp)

target_link_libraries(MyEngine freeglut glew32 opengl32 boost_system-mgw62-mt-1_62 boost_filesystem-mgw62-mt-1_62 assimp zlibstatic png)
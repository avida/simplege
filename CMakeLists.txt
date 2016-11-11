cmake_minimum_required(VERSION 3.7)
set (LIBS_DIR d:/libs)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(".",
                    "./3rdParty/ogl",
                    "${LIBS_DIR}/glew/include", 
                    "${LIBS_DIR}/freeglut/include", 
                    "${LIBS_DIR}/boost",
                    "${LIBS_DIR}/gmtl",
                    "${LIBS_DIR}/assimp/include")

link_directories("${LIBS_DIR}/freeglut/src",
                 "${LIBS_DIR}/glew/lib",
                 "${LIBS_DIR}/boost/bin.v2/libs/system/",
                 "${LIBS_DIR}/boost/bin.v2/libs/filesystem/",
                 "${LIBS_DIR}/assimp/build/code",
                 "${LIBS_DIR}/png")

add_executable(simplegl 
                        main.cpp 
                        opengl_application.cpp 
                        event_handler.cpp 
                        model_factory.cpp
                        model_factory_manager.cpp
                        shader_factory.cpp
                        utils/utils.cpp
                        utils/logger.cpp
                        ./3rdParty/ogl/math_3d.cpp  
                        model.cpp
                        camera.cpp
                        lighting.cpp)

target_link_libraries(simplegl freeglut glew32 opengl32 boost_system boost_filesystem assimp zlib png)
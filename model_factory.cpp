#include "model_factory.hpp"
#include <gmtl/gmtl.h>
#include <iostream>
#include <memory>

ModelFactory::ModelFactory()
{
}

void ModelFactory::init_instance()
{
    std::cout << "init !!!" << std::endl;
    // gmtl::Vec3f Vertices[] = {  {-1.0f, -1.0f, 0.5773f},
    //                              {0.0f, -1.0f, -1.15475f},
    //                              {1.0f, -1.0f, 0.5773f},
    //                              {0.0f, 1.0f, 0.0f}};
    gmtl::Vec3f Vertices[] = {  {-0.5f, 0.5f, .0f},
                                {-0.5f, -0.5f, .0f},
                                {0.5f, -0.25f, .0f},
                                {0.5f, 0.25f, .0f}};
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    unsigned int Indices[] = { 1, 0, 3,
                               1, 3, 2,
                             };
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    m_indices = sizeof(Indices) / sizeof(unsigned int); 
}

ModelPtr ModelFactory::CreateModel()
{
    return ModelPtr();
}

void ModelFactory::UtilizeModel(const ModelPtr&)
{
}

void ModelFactory::RenderModels()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0/*attribute index*/,
                          3/*number of components in the attribute*/, 
                          GL_FLOAT /*data type */, 
                          GL_FALSE /*normalize data before using in pipe*/, 
                          0 /* number of bytes between two instances of that 
                               attribute in the bufferstride */,
                          0 /* attribute offset inside structure */);
    glDrawElements(GL_TRIANGLES, m_indices /*number of indexes in the index buffer*/,
                   GL_UNSIGNED_INT /* index type */ , 
                   0/*offset in bytes from the start of the index 
                      buffer to the location of the first index to scan*/);
}
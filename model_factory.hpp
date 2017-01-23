#pragma once

#include <GL/glew.h>
#include <list>

#include "model.hpp"

class ModelFactory;

typedef boost::shared_ptr<ModelFactory> ModelFactoryPtr;
typedef std::list<ModelPtr> ModelList; 

class ModelFactory
{
public:
    ModelPtr CreateModel();
    void UtilizeModel(const ModelPtr& model);
    void RenderModels();
    ModelFactory(const std::string& fileName,const std::string& texture);
private:
    void LoadModel(const std::string& fileName,const std::string& texture);
    ModelList m_models;
    GLuint m_VBO = 0;
    GLuint m_IBO = 0;
    unsigned int m_indices;
    TexturePtr m_texture;

};
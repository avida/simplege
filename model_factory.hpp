#pragma once

#include <GL/glew.h>
#include <list>

#include "model.hpp"
#include "generic/singleton.hpp"


class ModelFactory;

typedef std::unique_ptr<ModelFactory> ModelFactoryPtr;
typedef std::list<ModelPtr> ModelList; 

class ModelFactory : public generic::singleton<ModelFactory>
{
friend generic::singleton<ModelFactory>;
public:
    ModelPtr CreateModel();
    void UtilizeModel(const ModelPtr& model);
    void RenderModels();
protected:
    ModelFactory();
    void init_instance();
private:
    void SetupFactory();
    ModelList m_models;
    GLuint m_VBO;
    GLuint m_IBO;
    unsigned int m_indices;
};
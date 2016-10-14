#pragma once

#include <map>

#include "model_factory.hpp"
#include "generic/singleton.hpp"

class ModelFactoryManager : public generic::singleton<ModelFactoryManager>
{
friend generic::singleton<ModelFactoryManager>;
public:
   ModelFactoryPtr SetupFactory(const std::string& factoryName, const std::string& fileName);
   ModelFactoryPtr GetFactory(const std::string& factoryName);
   void FactoriesRender();
protected:
   void init_instance();
   std::map<std::string, ModelFactoryPtr> m_factories;
};

#include "model_factory_manager.hpp"

#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include "utils/logger.hpp"

const std::string model_directory = "../models/";
const std::string textures_directory = "../textures/";

void ModelFactoryManager::init_instance()
{

}
ModelFactoryPtr ModelFactoryManager::SetupFactory(const std::string& factoryName, 
                                                  const std::string& fileName,
                                                  const std::string& texture)
{
   auto& factory_ptr = m_factories[factoryName];
   if (factory_ptr)
   {
      gl::Log(boost::format("Cannot setup model factory %1% beacuse its already exists") % factoryName);
   }
   auto ptr = boost::make_shared<ModelFactory>(model_directory + fileName, texture.empty() ? texture : textures_directory + texture);
   factory_ptr.swap(ptr);
   return factory_ptr;
}

void ModelFactoryManager::FactoriesRender()
{
   BOOST_FOREACH(auto& factory_it, m_factories)
   {
      factory_it.second->RenderModels();
   }
}

ModelFactoryPtr ModelFactoryManager::GetFactory(const std::string& factoryName)
{
   return m_factories[factoryName];
}
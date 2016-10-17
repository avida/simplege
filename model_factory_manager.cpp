#include "model_factory_manager.hpp"

#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include "utils/logger.hpp"

void ModelFactoryManager::init_instance()
{

}

ModelFactoryPtr ModelFactoryManager::SetupFactory(const std::string& factoryName, const std::string& fileName)
{
   auto& factory_ptr = m_factories[factoryName];
   if (factory_ptr)
   {
      gl::Log(boost::format("Cannot setup model factory %1% beacuse its already exists") % factoryName);
   }
   auto ptr = boost::make_shared<ModelFactory>(fileName);
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
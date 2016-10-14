#include "model_factory.hpp"
#include "model.hpp"
#include "utils/logger.hpp"
#include <boost/make_shared.hpp>
#include <gmtl/gmtl.h>
#include <memory>

// #include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>    // Post processing flags


ModelFactory::ModelFactory(const std::string& fileName)
{
  LoadModel(fileName);
}

void ModelFactory::LoadModel(const std::string& fname)
{
   if (m_VBO || m_IBO)
      return;
   Assimp::Importer Importer;

   auto pScene = Importer.ReadFile(fname.c_str(),
                               aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
   if (pScene) 
   {
      if (!pScene->mNumMeshes)
      {
          gl::Log(boost::format("Cannot find mode in %1%") % fname);
      }
      std::vector<gmtl::Vec3f> vertexes;
      auto mesh = pScene->mMeshes[0];
      vertexes.resize(mesh->mNumVertices);
      for (auto i = 0; i < mesh->mNumVertices; ++i)
      {
          const aiVector3D* pPos = &(mesh->mVertices[i]);
          vertexes[i][0] = pPos->x;
          vertexes[i][1] = pPos->y;
          vertexes[i][2] = pPos->z;
      }
      glGenBuffers(1, &m_VBO);
      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(gmtl::Vec3f) * vertexes.size(), &vertexes[0], GL_STATIC_DRAW);

      std::vector<unsigned int> indices;
      indices.resize(mesh->mNumFaces * 3);
      for (auto i = 0 ; i < mesh->mNumFaces ; i++)
      {
            auto& face = mesh->mFaces[i];
            assert(face.mNumIndices == 3);
            indices[i*3] = face.mIndices[0];
            indices[i*3 + 1] = face.mIndices[1];
            indices[i*3 + 2] = face.mIndices[2];
      }
      glGenBuffers(1, &m_IBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int) , &indices[0], GL_STATIC_DRAW);
      m_indices = indices.size(); 
  }
  else
  {
       gl::Log(boost::format("Failed to load file %1%") % fname);
  } 
}

ModelPtr ModelFactory::CreateModel()
{
    auto model = boost::make_shared<Model>();
    m_models.push_front(model);
    return model;
}

void ModelFactory::UtilizeModel(const ModelPtr& model)
{
  m_models.remove(model);
}

void ModelFactory::RenderModels()
{
    if (m_models.empty())
    {
        return;
    }
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
    for(auto model:m_models)
    {
      model->Render();
      glDrawElements(GL_TRIANGLES, m_indices /*number of indexes in the index buffer*/,
                     GL_UNSIGNED_INT /* index type */ , 
                     0/*offset in bytes from the start of the index 
                        buffer to the location of the first index to scan*/);
    }
}
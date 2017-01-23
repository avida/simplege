#include "model_factory.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "utils/logger.hpp"
#include <boost/make_shared.hpp>
#include <math_3d.hpp>
#include <memory>

// #include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>    // Post processing flags


ModelFactory::ModelFactory(const std::string& fileName, const std::string texture)
{
  LoadModel(fileName, texture);
}

struct Vertex 
{
  Vector3f pos;
  Vector3f norm;
  Vector2f texture;
};

void ModelFactory::LoadModel(const std::string& fname, std::string texture)
{
   if (m_VBO || m_IBO)
      return;
   Assimp::Importer Importer;
   static const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

   auto pScene = Importer.ReadFile(fname.c_str(),
                               aiProcess_Triangulate | aiProcess_GenSmoothNormals  | aiProcess_FlipUVs);
   if (pScene) 
   {
      if (!pScene->mNumMeshes)
      {
          gl::Log(boost::format("Cannot find mode in %1%") % fname);
      }
      std::vector<Vertex> vertexes;
      auto mesh = pScene->mMeshes[0];
      vertexes.resize(mesh->mNumVertices);
      for (auto i = 0; i < mesh->mNumVertices; ++i)
      {
          const aiVector3D* pPos = &(mesh->mVertices[i]);
          const aiVector3D* pNormal = &(mesh->mNormals[i]);
          const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
          vertexes[i].pos.x = pPos->x;
          vertexes[i].pos.y = pPos->y;
          vertexes[i].pos.z = pPos->z;
          vertexes[i].norm.x = pNormal->x;
          vertexes[i].norm.y = pNormal->y;
          vertexes[i].norm.z = pNormal->z;
          vertexes[i].texture.x = pTexCoord->x;
          vertexes[i].texture.y = pTexCoord->y;
          // gl::Log(boost::format("x: %1% y: %2% z: %3%") % pNormal->x % pNormal->y% pNormal->z  ); 
      }
      std::vector<unsigned int> indices;
      indices.resize(mesh->mNumFaces * 3);
      for (auto i = 0 ; i < mesh->mNumFaces ; i++)
      {
            auto& face = mesh->mFaces[i];
            assert(face.mNumIndices == 3);
            indices[i*3] = face.mIndices[0];
            indices[i*3 + 1] = face.mIndices[1];
            indices[i*3 + 2] = face.mIndices[2];
            // vertexes[face.mIndices[0]].texture = {0, 0};
            // vertexes[face.mIndices[1]].texture = {1, 0};
            // vertexes[face.mIndices[2]].texture = {1, 1};
      }
      glGenBuffers(1, &m_VBO);
      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexes.size(), &vertexes[0], GL_STATIC_DRAW);

      glGenBuffers(1, &m_IBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int) , &indices[0], GL_STATIC_DRAW);
      m_indices = indices.size(); 
  }
  else
  {
       gl::Log(boost::format("Failed to load file %1%") % fname);
  }
  if (!texture.empty())
  {
    m_texture = boost::make_shared<Texture>();
    m_texture->Load(texture);
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
    glEnableVertexAttribArray(1);
    if (m_texture)
    {
      glEnableVertexAttribArray(2);
      m_texture->Bind();
    }
    glVertexAttribPointer(0/*attribute index*/,
                          3/*number of components in the attribute*/, 
                          GL_FLOAT /*data type */, 
                          GL_FALSE /*normalize data before using in pipe*/, 
                          sizeof(Vertex) /* number of bytes between two instances of that 
                                         attribute in the bufferstride */,
                          0 /* attribute offset inside structure */);
    // Normals
    glVertexAttribPointer(1, 3 ,GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)sizeof(Vector3f));
    // Texture Coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(2 * sizeof(Vector3f)));
    for(auto model:m_models)
    {
      model->Render();
      glDrawElements(GL_TRIANGLES, m_indices /*number of indexes in the index buffer*/,
                     GL_UNSIGNED_INT /* index type */ , 
                     0/*offset in bytes from the start of the index 
                        buffer to the location of the first index to scan*/);
    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
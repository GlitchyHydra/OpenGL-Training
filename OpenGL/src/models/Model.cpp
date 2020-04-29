#include "Model.h"

#include <iostream>

Model::Model(std::string& path) : mFilePath(path)
{
    loadModel();
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // обработать все полигональные сетки в узле(если есть)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // выполнить ту же обработку и для каждого потомка узла
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::loadModel() 
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(mFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    //verticies
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vectorPosition(mesh->mVertices[i].x,
            mesh->mVertices[i].y, mesh->mVertices[i].z);
        glm::vec3 vectorNormal (mesh->mNormals[i].x,
            mesh->mNormals[i].y, mesh->mNormals[i].z);
        glm::vec2 texCoords(0.f, 0.f);
        if (mesh->mTextureCoords[0])
        {
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
        }

        vertices.push_back({vectorPosition, vectorNormal, texCoords});
    }

    //indicies
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    //different texures: diffuse and etc.
    if (mesh->mMaterialIndex >= 0)
    {

    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        //texture.id = TextureFromFile(str.C_Str(), directory);
        //texture.type = typeName;
        //texture.path = str;
        textures.push_back(texture);
    }

    return textures;
}

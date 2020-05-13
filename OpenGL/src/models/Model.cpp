#include "Model.h"

#include <iostream>

Model::Model(const std::string& path) :
    mFilePath(path)
{
    loadModel();
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

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // обработать все полигональные сетки в узле(если есть)
    meshes.resize(scene->mNumMeshes);
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        processMesh(scene->mMeshes[i], scene, meshes[i]);
    }

    textures.resize(scene->mNumMaterials);
    InitTextures(scene, mFilePath);
}

void Model::processMesh(aiMesh* ai_Mesh, const aiScene* scene, Mesh& mesh)
{
    mesh.matInd = ai_Mesh->mMaterialIndex;
    //verticies
    for (unsigned int i = 0; i < ai_Mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vectorPosition(ai_Mesh->mVertices[i].x,
            ai_Mesh->mVertices[i].y, ai_Mesh->mVertices[i].z);
        glm::vec3 vectorNormal (ai_Mesh->mNormals[i].x,
            ai_Mesh->mNormals[i].y, ai_Mesh->mNormals[i].z);
        glm::vec2 texCoords(0.f, 0.f);
        if (ai_Mesh->mTextureCoords[0])
        {
            texCoords.x = ai_Mesh->mTextureCoords[0][i].x;
            texCoords.y = ai_Mesh->mTextureCoords[0][i].y;
        }

        mesh.vertices.push_back({vectorPosition, vectorNormal, texCoords});
    }

    //indicies
    for (unsigned int i = 0; i < ai_Mesh->mNumFaces; i++)
    {
        aiFace& face = ai_Mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            mesh.indices.push_back(face.mIndices[j]);
    }

    mesh.SetupMesh();
}

void Model::InitTextures(const aiScene* scene, const std::string& Filename)
{
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos)
    {
        Dir = ".";
    }
    else if (SlashIndex == 0)
    {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }

    for (unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        const aiMaterial* aiMat = scene->mMaterials[i];
        textures[i] = NULL;
        if (aiMat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString Path;
            //other parameters in Func GetTexture is NULL
            bool getRes = aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &Path);
            if (getRes == AI_SUCCESS)
            {
                std::string FullPath = Dir + "/" + Path.data;
                textures[i] = new Texture(FullPath.c_str(), i, TextureType::DIFFUSE );
                //textures[i]->Bind();
            }
        }
    }
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(aiType); i++)
    {
        aiString str;
        mat->GetTexture(aiType, i, &str);
        std::cout << "texture: " << str.C_Str() << std::endl;
        textures.push_back(Texture(str.C_Str(), i % 33));
    }

    return textures;
}

void Model::Draw(Shader& shader, const Renderer& renderer) const
{
    for (auto& mesh : meshes) {
        mesh.Bind();
        this->textures[mesh.matInd]->Bind();
        this->textures[mesh.matInd]->SetTexture(shader);
        renderer.Draw(mesh.va, mesh.ib, shader);
        mesh.va.Unbind();
    }
}
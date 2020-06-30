#include "Scene.h"

#include <iostream>

namespace My_OpenGL {

    Scene::Scene(Shader& shader) : light(new Light(shader)), camera(new Camera())
    {
        camera->SetEyeInShader(shader);

        light->SetDirectLights(shader);
        light->SetPointLights(shader);
    }

    Scene::~Scene()
    {
        delete light;
        delete camera;
        for (Model* model : models)
        {
            delete model;
        }
    }

    void Scene::AddModel(const std::string& path)
    {
        models.emplace_back(new Model(path));
    }

    Scene* Scene::CreateScene(Shader& shader)
    {
        return new Scene(shader);
    }

    void Scene::setView(glm::mat4& model, Shader& shader) const
    {
        glm::mat4 mvp = proj * camera->GetView() * model;
        shader.SetUniformMat4f("u_MVP", mvp);
    }

    std::vector<Model*>& Scene::GetModels() 
    {
        return models;
    }

    Light* Scene::GetLight() const
    {
        return light;
    }

    Camera* Scene::GetCamera() const
    {
        return camera;
    }
};
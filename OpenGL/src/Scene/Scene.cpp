#include "Scene.h"

#include <iostream>

namespace My_OpenGL {

    Scene::Scene(Shader& shader) : light(new Light(shader)), camera(new Camera())
    {
        skybox = nullptr;

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

    void Scene::SetupSkybox()
    {
        skybox = new Skybox(camera);
        skybox->SetShader(new Shader("res/shaders/Skybox.shader"));

        skybox->GetShader()->Bind();
        skybox->Init(".",
            "res/skybox/sp3right.jpg",
            "res/skybox/sp3left.jpg",
            "res/skybox/sp3top.jpg",
            "res/skybox/sp3bot.jpg",
            "res/skybox/sp3front.jpg",
            "res/skybox/sp3back.jpg");
        skybox->GetShader()->Unbind();
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
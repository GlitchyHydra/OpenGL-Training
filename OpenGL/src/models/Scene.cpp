#include "Scene.h"

#include <iostream>

namespace My_OpenGL {

    void Scene::setView(glm::mat4& model, Shader& shader) const
    {
        //glm::mat4 mvp = proj * camera.GetView() * model;
        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
        //std::cout << camera.GetView()[3][3] << std::endl;
        glm::mat4 mvp = proj * camera.GetView() * model;
        glm::vec3 vv(0.f, 0.f, 0.f);
        shader.SetUniform3f("gEyeWorldPos", vv.x, vv.y, vv.z);
        shader.SetUniformMat4f("u_MVP", mvp);
    }

};
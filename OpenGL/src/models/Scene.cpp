#include "Scene.h"

namespace My_OpenGL {

    void Scene::setView(glm::mat4& model, Shader& shader) const
    {
        //glm::mat4 mvp = proj * camera.GetView() * model;
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
        glm::mat4 mvp = proj * view * model;
        shader.SetUniformMat4f("u_MVP", mvp);
    }

    void Scene::calculateAndSet(double& time, glm::mat4& model, Shader& shader) const
    {
        glm::mat4 mvp = proj * camera.GetView(time) * model;
        /*
                  | 1, 0, 0, View_x|    | 1, 0, 0, Model_x|   | 1, 0, 0, View_x + Model_x|
                  | 0, 1, 0, View_y|    | 0, 1, 0, Model_y| = | 0, 1, 0, View_y + Model_y|
                  | 0, 0, 1, View_z|    | 0, 0, 1, Model_z|   | 0, 0, 1, View_z + Model_z|
                  | 0, 0, 0, 1     |    | 0, 0, 0, 1      |   | 0, 0, 0, 1      |
        */
        shader.SetUniformMat4f("u_MVP", mvp);
    }
};
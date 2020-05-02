#include "Scene.h"

void My_OpenGL::Scene::calculateAndSet(glm::mat4& model, Shader& shader) const
{
	glm::mat4 mvp = proj * view * model;
    /*
              | 1, 0, 0, View_x|    | 1, 0, 0, Model_x|   | 1, 0, 0, View_x + Model_x|
              | 0, 1, 0, View_y|    | 0, 1, 0, Model_y| = | 0, 1, 0, View_y + Model_y|
              | 0, 0, 1, View_z|    | 0, 0, 1, Model_z|   | 0, 0, 1, View_z + Model_z|
              | 0, 0, 0, 1     |    | 0, 0, 0, 1      |   | 0, 0, 0, 1      |
    */
	shader.SetUniformMat4f("u_MVP", mvp);
}

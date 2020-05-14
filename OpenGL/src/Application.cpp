#include "OpenGL_config.h"
#include <iostream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "models/Light.h"
#include "models/Model.h"


int main(void)
{
    My_OpenGL::Config cfg;
    GLFWwindow* window = cfg.GetWindow();
    Renderer renderer;

    Model model("res/models/E4/E 45 Aircraft_obj.obj");

    Shader shader("res/shaders/Model.shader");
    shader.Bind();
    scene.camera.SetEyeInShader(shader);
    model.SetModelTrans(shader);

    My_OpenGL::Light light(shader);
    light.SetDirectLights(shader);
    light.SetPointLights(shader);

    shader.Unbind();
    scene.camera.Print();

    glEnable(GL_DEPTH_TEST);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer.Clear();
        
        {
            shader.Bind();
            glm::mat4 modelTs = glm::translate(glm::mat4(1.0f), model.translation);
            //model = glm::rotate(model, -45.0f, translationA);
            modelTs[0][0] = model.scale.x;
            modelTs[1][1] = model.scale.y;
            modelTs[2][2] = model.scale.z;
            scene.setView(modelTs, shader);
            model.SetModelTrans(shader);

            model.Draw(shader, renderer);
            //glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Hello, world!");    
            ImGui::Text("Model");
            ImGui::SliderFloat3("TranslationA", &model.translation.x, 0.0f, 1920.0f);        
            ImGui::SliderFloat3("ScaleA", &model.scale.x, 0.1f, 100.0f);
            ImGui::Text("Camera");
            ImGui::SliderFloat3("RotationCamera", &scene.camera.target.x, -12.0f, 12.0f);
            ImGui::SliderFloat3("MoveCamera", &scene.camera.position.x, -1920.0f, 1920.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    return 0;
}
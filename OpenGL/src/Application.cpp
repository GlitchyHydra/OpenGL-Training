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

#include "primitives/Cube.h"
#include "models/Light.h"
//#include "models/Model.h"

int main(void)
{
    My_OpenGL::Config cfg;
    GLFWwindow* window = cfg.GetWindow();
    Renderer renderer;
    Cube cube;
    cube.va.Unbind();
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    Texture texture("res/textures/container.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    My_OpenGL::Light light(shader);
    shader.SetUniformMat4f("gWorld", glm::ortho(0.f, 1920.0f, 0.f, 1080.0f, -1000.0f, 1000.0f));

    shader.Unbind();

    glm::vec3 translationA(960.f, 540.f, 10.f);
    glm::vec3 scaleA(1.f, 1.f, 1.f);

    float angle = 0.0f;

    glEnable(GL_DEPTH_TEST);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer.Clear();
        
        {
            shader.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            //model = glm::rotate(model, -45.0f, translationA);
            /*model[0][0] = scaleA.x;
            model[1][1] = scaleA.y;
            model[2][2] = scaleA.z;*/
            double time = glfwGetTime();
            scene.setView(model, shader);
            //scene.calculateAndSet(time, model, shader);
            renderer.Draw(cube.va, cube.ib, shader);
            //glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
        }
        angle += 100;
        if (angle >= 360)
        {
            angle = 0.f;
        }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 1920.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat3("ScaleA", &scaleA.x, 0.1f, 2.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //ImGui::SliderFloat("Camera", &height, 0.0f, 1080.0f);
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
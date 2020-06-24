#include "Application.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace My_OpenGL {

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    Application* CreateApplication()
    {
        return new Application();
    }

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        renderer = std::make_unique<Renderer>();
        
        if (glewInit() != GLEW_OK) {
            std::cout << "error";
        }

        shader = new Shader("res/shaders/Model.shader");
        shader->Bind();
        m_Scene = std::unique_ptr<Scene>(Scene::CreateScene(*shader));
    }

    Application::~Application() {

    }

    /*void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PopOverlay(layer);
    }
    */
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

        //VIPERA_CORE_TRACE("(0)", e);

        /*for (auto it = m_LayerStack.end(); it != m_LayerStack.begin())
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }*/
    }

    void Application::Run() {
        //shader->Unbind();
        glEnable(GL_DEPTH_TEST);

        while (m_Running)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            /*for (Layer* layer : m_LayerStack)
                layer->OnUpdate();*/
            renderer->Clear();
            Model* model = m_Scene->GetModels()[0];

            glm::mat4 modelTs = glm::translate(glm::mat4(1.0f), model->translation);
            //model = glm::rotate(model, -45.0f, translationA);
            modelTs[0][0] = model->scale.x;
            modelTs[1][1] = model->scale.y;
            modelTs[2][2] = model->scale.z;
            m_Scene->setView(modelTs, *shader);

            model->SetModelTrans(*shader);

            model->Draw(*shader, *renderer);
            //renderer->Draw(model->va, ib, shader);

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
/*
int main(void)
{
    //model.SetModelTrans(shader);

    while (true)
    {
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

        {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            ImGui::SliderFloat3("Translation", (&model.translation.x), 0.0f, 1920.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat3("Scale", (&model.scale.x), 1.0f, 1000.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }
    return 0;
}*/

int main(int argc, char** argv) {
    auto app = My_OpenGL::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

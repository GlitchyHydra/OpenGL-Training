#include "Application.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ImGUI/ImGuiLayer.h"

namespace My_OpenGL {

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

    Application* Application::s_Application = nullptr;

    Application* CreateApplication()
    {
        return new Application();
    }

    Application::Application()
    {
        s_Application = this;

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

    Application::~Application()
    {

    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(Application::OnKeyReleased));

        //std::cout << e.ToString() << std::endl;

        /*for (auto it = m_LayerStack.end(); it != m_LayerStack.begin())
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }*/
    }

	void Application::PushLayer(ImGuiLayer* layer)
	{
        m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(ImGuiLayer* layer)
	{
        m_LayerStack.PopLayer(layer);
	}

    void Application::Run() {
        //shader->Unbind();
        glEnable(GL_DEPTH_TEST);

        while (m_Running)
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            renderer->Clear();

            //Layers render
            ImGuiLayer::Begin();
            for (ImGuiLayer* layer : m_LayerStack)
                layer->Render();
            ImGuiLayer::End();

            //Models render
            Model* model = m_Scene->GetModels()[0];

            {
                glm::mat4 modelTs = glm::translate(glm::mat4(1.0f), model->translation);
                glm::scale(modelTs, model->scale);
                modelTs[0][0] = model->scale.x;
                modelTs[1][1] = model->scale.y;
                modelTs[2][2] = model->scale.z;
                m_Scene->setView(modelTs, *shader);

                model->SetModelTrans(*shader);
            }

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

    bool Application::OnKeyReleased(KeyReleasedEvent& e)
    {
        switch (e.GetKeyCode()) {
            case GLFW_KEY_W:
            {
                //std::cout << "W" << std::endl;
                m_Scene->GetCamera()->Up();
            } break;
            case GLFW_KEY_S:
            {
                //std::cout << "S" << std::endl;
                m_Scene->GetCamera()->Down();
            } break;
            case GLFW_KEY_A:
            {
                //std::cout << "A" << std::endl;
                m_Scene->GetCamera()->Left();
            } break;
            case GLFW_KEY_D:
            {
                //std::cout << "D" << std::endl;
                m_Scene->GetCamera()->Right();
            } break;
        }

        return true;
    }
}

int main(int argc, char** argv) {
    auto app = My_OpenGL::CreateApplication();
    app->PushLayer(new My_OpenGL::ImGuiLayer("Manage Models"));
    app->Run();
    delete app;
    return 0;
}

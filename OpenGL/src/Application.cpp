﻿#include "Application.h"

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
        
        shader = new Shader("res/shaders/Model.shader");
        shader->Bind();
        m_Scene = std::unique_ptr<Scene>(Scene::CreateScene(*shader));
        m_Scene->AddModel("res/models/E4/E 45 Aircraft_obj.obj");

        shader->Unbind();

        m_Scene->SetupSkybox();

        ImGuiLayerData* imgd = new My_OpenGL::ImGuiLayerData();
        

        PushLayer(imgd);
        PushLayer(new My_OpenGL::ImGuiViewportLayer(m_Scene.get(), renderer->GetFrameBuffer()));

        Model* model = m_Scene->GetModels()[0];

        ModelData* modelData = new ModelData(model->GetTranslation(),
            model->GetRotation(),
            model->GetScale());

        imgd->PushData(modelData, m_Scene->GetLight());

        ImGuiLayer::Init();
    }

    Application::~Application()
    {

    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(Application::OnMouseMoved));
        //dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(Application::OnKeyReleased));

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

    void Application::CheckForMoveCamera()
    {
        if (IsKeyPressed(GLFW_KEY_W))
            m_Scene->GetCamera()->Forward();
        if (IsKeyPressed(GLFW_KEY_S))
            m_Scene->GetCamera()->Back();
        if (IsKeyPressed(GLFW_KEY_A))
            m_Scene->GetCamera()->Left();
        if (IsKeyPressed(GLFW_KEY_D))
            m_Scene->GetCamera()->Right();

        auto window = static_cast<GLFWwindow*>(GetWindow().GetNativeWindow());
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && !mousePosCalculated)
        {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            mouseEndPos = glm::vec2((float)x, (float)y);
            std::cout << "Mouse" << std::endl;
            float deltaX = mouseEndPos.x - mouseBeginPos.x;
            float deltaY = mouseEndPos.y - mouseBeginPos.y;
            std::cout << "X: " << deltaX << std::endl;
            std::cout << "Y: " << deltaY << std::endl;

            mouseBeginPos = mouseEndPos;

            float sensitivity = 0.1f;
            glm::vec2 rotationVec = glm::vec2(deltaX * sensitivity, deltaY * sensitivity);
            m_Scene->GetCamera()->SetRotation(rotationVec);

            mousePosCalculated = true;
            //glm::rotate()
        }
    }

    bool Application::OnMouseMoved(MouseMovedEvent& event)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        
        auto state = glfwGetKey(window, GLFW_KEY_LEFT_ALT);
        if (state == GLFW_PRESS && mousePosCalculated)
        {
            mouseBeginPos = glm::vec2(event.GetX(), event.GetY());
            mousePosCalculated = false;
        }
        return false;
    }

    void Application::Run() {
        glEnable(GL_DEPTH_TEST);
        while (m_Running)
        {
            renderer->GetFrameBuffer()->Bind();
            renderer->Clear();

            //Camera Movement
            CheckForMoveCamera();

            //Models render
            
            renderer->Draw(*m_Scene.get(), *shader);
            m_Scene->GetSkybox()->Render(m_Scene->GetProj(), *renderer);

            //renderer->Draw(model->va, ib, shader);

            renderer->GetFrameBuffer()->Unbind();
            //Layers render
            ImGuiLayer::Update(m_LayerStack);

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::IsKeyPressed(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, button);
        return state == GLFW_PRESS;
    }

}

int main(int argc, char** argv) {
    auto app = My_OpenGL::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

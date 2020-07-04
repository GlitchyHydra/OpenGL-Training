#pragma once

#include "ImGUI/ImGuiLayer.h"
#include "ImGUI/ImGuiViewportLayer.h"

#include "Layer/LayerStack.h"
#include "Window/Window.h"
#include "Scene/Scene.h"

namespace My_OpenGL {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		inline static Application& Get() { return *s_Application; };
		inline Window& GetWindow() const { return *m_Window; };

		void Run();

		void OnEvent(Event& e);

		bool OnMouseMoved(MouseMovedEvent& event);

		void PushLayer(ImGuiLayer* layer);
		void PushOverlay(ImGuiLayer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool IsKeyPressed(int button);
		void CheckForMoveCamera();
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Scene> m_Scene;
		Shader* shader; 

		bool m_Running = true;
		LayerStack m_LayerStack;

		bool mousePosCalculated = true;
		glm::vec2 mouseBeginPos;
		glm::vec2 mouseEndPos;
	private:
		static Application* s_Application;

	};

	Application* CreateApplication();

}
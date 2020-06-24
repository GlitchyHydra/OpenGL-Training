#pragma once

//#include "LayerStack.h"
#include "Window/Window.h"
#include "Scene/Scene.h"

namespace My_OpenGL {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		//void PushLayer(Layer* layer);
		//void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Scene> m_Scene;
		Shader* shader; 

		bool m_Running = true;
		//LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}
#pragma once

#include <vector>
#include "ImGUI/ImGuiLayer.h"

namespace My_OpenGL {
	
	class LayerStack
	{
	public:
		LayerStack() {};
		~LayerStack();

		void PushLayer(ImGuiLayer* imguilayer);
		void PopLayer(ImGuiLayer* imguilayer);

		std::vector<ImGuiLayer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<ImGuiLayer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<ImGuiLayer*> m_Layers;
	};

}


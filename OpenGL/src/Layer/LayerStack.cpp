#include "LayerStack.h"

namespace My_OpenGL {
	
	LayerStack::~LayerStack()
	{
		for (ImGuiLayer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(ImGuiLayer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(ImGuiLayer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			//m_LayerInsertIndex--;
			layer->OnDetach();
		}
	}
}
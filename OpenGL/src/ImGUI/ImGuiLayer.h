#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace My_OpenGL {

	class ImGuiLayer
	{
	public: 
		ImGuiLayer(const std::string name);
		~ImGuiLayer();

		void OnAttach() const;
		void OnDetach() const;

		static void Begin();
		static void End();
		void Render() const;

	private:
		std::string m_Name;

		struct ModelData
		{
			glm::vec3* translation;
			glm::vec3* rotation;
			glm::vec3* scale;
		};

		std::vector<ModelData*> m_ModelData;
	};
}
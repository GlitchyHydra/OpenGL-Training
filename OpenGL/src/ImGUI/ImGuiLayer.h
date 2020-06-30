#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace My_OpenGL {

	struct ModelData
	{
		glm::vec3& translation;
		glm::vec3& rotation;
		glm::vec3& scale;

		ModelData(glm::vec3& t, glm::vec3& r, glm::vec3& s)
			: translation(t), rotation(r), scale(s)
		{}
	};

	class ImGuiLayer
	{
	public: 
		ImGuiLayer(const std::string name);
		~ImGuiLayer();

		void OnAttach() const;
		void OnDetach() const;

		static void Begin();
		static void End();
		virtual void Render() const;

		void PushData(ModelData* data);

		const std::string& GetName();

	private:
		std::string m_Name;

		ModelData* m_ModelData;
	};
}
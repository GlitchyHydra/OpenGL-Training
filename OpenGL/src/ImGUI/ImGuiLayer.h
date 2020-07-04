#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Scene/Light/Light.h"

namespace My_OpenGL {

	class LayerStack;

	struct ModelData
	{
		glm::vec3& translation;
		glm::vec3& rotation;
		glm::vec3& scale;

		ModelData(glm::vec3& t, glm::vec3& r, glm::vec3& s)
			: translation(t), rotation(r), scale(s)
		{}
	};

	struct LightData
	{
		std::vector<DirectionalLight>& directionalLights;
		std::vector<PointLight>& pointLights;

	};

	class ImGuiLayer
	{
	public: 
		ImGuiLayer(const std::string name);
		virtual ~ImGuiLayer();

		static void Init();
		static void Shutdown();

		static void ShowDockSpace(bool* p_open);
		static void Update(LayerStack& layerStack);

		virtual void Begin() const;
		virtual void End() const;
		virtual void Render() const;

		const std::string& GetName() const;

	private:
		std::string m_Name;
	};


	class ImGuiLayerData : public ImGuiLayer
	{
	public:
		ImGuiLayerData();
		virtual ~ImGuiLayerData();

		virtual void Render() const override;

		void PushData(ModelData* data, Light* light);

	private:
		ModelData* m_ModelData;
		LightData* m_LightData;
	};
}
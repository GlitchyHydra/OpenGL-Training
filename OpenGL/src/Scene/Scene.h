#pragma once

#include <vector>

#include "abstractions/Shader.h"
#include "Scene/Camera/Camera.h"
#include "Scene/Model/Model.h"
#include "Scene/Light/Light.h"
#include "Scene/Skybox/Skybox.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace My_OpenGL {
	class Scene
	{
	public: 
		static Scene* CreateScene(Shader& shader);

		Scene(Shader& shader);
		~Scene();

		void SetupSkybox();

		void AddModel(const std::string& path);
		void setView(glm::mat4& model, Shader& shader) const;

		//Get Scene Attributes
		std::vector<Model*>& GetModels();
		Light* GetLight() const;
		Camera* GetCamera() const;
		Skybox* GetSkybox() const { return skybox; }
		const glm::mat4& GetProj() const { return proj; }

	private:
		glm::mat4 proj = glm::perspective((float)glm::radians(45.0f), 1920.0f / 1080.0f, -1.0f, 100.0f);
		//glm::mat4 proj = glm::ortho(0.f, 1920.0f, 0.f, 1080.0f, -10.0f, 4000.0f);
		std::vector<Model*> models;
		Light* light;
		Camera* camera;
		Skybox* skybox;
	};
};
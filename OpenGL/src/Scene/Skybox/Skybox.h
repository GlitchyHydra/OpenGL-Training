#pragma once

#include <string>

#include "Scene/Model/Model.h"
#include "Scene/Camera/Camera.h"
#include "CubemapTexture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace My_OpenGL {

	class Skybox
	{
	public:
		Skybox(Camera* pCamera);
		~Skybox();

		bool Init(
			const std::string& Directory,
			const std::string& PosXFilename,
			const std::string& NegXFilename,
			const std::string& PosYFilename,
			const std::string& NegYFilename,
			const std::string& PosZFilename,
			const std::string& NegZFilename
		);

		void SetShader(Shader* shader);

		void Render(const glm::mat4& proj, const Renderer& pRenderer);

		Shader* GetShader() { return skyboxShader; }

	private:
		Camera* m_Camera;
		CubemapTexture* m_CubemapTex;
		Model* m_Mesh;
		Shader* skyboxShader;

		glm::vec3 scale { 4000.0f, 4000.0f, 4000.0f };
		glm::vec3 rotate { 0.0f, 0.0f, 0.0f };
	};

};
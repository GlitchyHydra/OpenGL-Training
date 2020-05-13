#pragma once

#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "Shader.h"

namespace My_OpenGL {

	struct BaseLight
	{
		glm::vec4 Color;
		float AmbientIntensity;
		float DiffuseIntensity;
		float SpecularIntensity;

		BaseLight()
		{
			Color = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
			AmbientIntensity = 0.0f;
			DiffuseIntensity = 0.0f;
			SpecularIntensity = 0.5f;
		}
	};

	struct PointLight : BaseLight
	{
		glm::vec3 Position;

		struct
		{
			float Constant;
			float Linear;
			float Exp;
		} Attenuation;

		PointLight()
		{
			Position = glm::vec3(0.0f, 0.0f, 0.0f);
			Attenuation.Constant = 1.0f;
			Attenuation.Linear = 0.0f;
			Attenuation.Exp = 0.0f;
		}
	};

	struct DirectionalLight : BaseLight
	{
		glm::vec3 Direction { 1000.f, 500.f, -50.0f };

		DirectionalLight()
		{
			Direction = glm::vec3(960.0f, 650.0f, -50.0f);
		}
	};

	class Light {
	private:
		std::vector<DirectionalLight> lightsDir;
		std::vector<PointLight> lightsPoint;

		const unsigned int lightsDirCount = 2;
		const unsigned int lightsPointCount = 7;
	public:
		Light(Shader& shader) {
			shader.SetUniform1ui("LIGHTS_DIR_COUNT;", lightsDirCount);
			shader.SetUniform1ui("LIGHTS_POINT_COUNT", lightsPointCount);
			BaseLight bl;
			lightsDir.push_back(DirectionalLight());
			lightsDir.push_back(DirectionalLight());
			lightsDir[0].Color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
			lightsDir[1].Color = glm::vec4(0.5f, 1.0f, 0.0f, 1.0f);
			
			/*for (unsigned int i = 0; i < lightsPointCount; i++)
			{
				lightsDir.push_back(DirectionalLight());
				lightsDir[i].AmbientIntensity =
			}*/
		};
	};
};

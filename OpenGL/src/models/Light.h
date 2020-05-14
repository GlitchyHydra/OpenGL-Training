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
			AmbientIntensity = 0.0005f;
			DiffuseIntensity = 0.2f;
			SpecularIntensity = 0.3f;
		}
	};

	struct DirectionalLight : BaseLight
	{
		glm::vec3 Direction{ 1000.f, 500.f, -50.0f };

		DirectionalLight()
		{
			Direction = glm::vec3(960.0f, 550.0f, -50.0f);
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
			Attenuation.Constant = 0.1f;
			Attenuation.Linear = 0.1f;
			Attenuation.Exp = 0.1f;
		}
	};

	class Light {
	private:
		std::vector<DirectionalLight> lightsDir;
		std::vector<PointLight> lightsPoint;

		const unsigned int lightsDirCount = 2;
		const unsigned int lightsPointCount = 3;
	public:
		Light(Shader& shader);
		void SetDirectLights(Shader& shader);
		void SetPointLights(Shader& shader);
	private:
		
	};
};

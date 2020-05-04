#pragma once

#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "Shader.h"

namespace My_OpenGL {

	struct DirectionalLight
	{
		glm::vec4 Color { 1.0f, 1.0f, 0.4f, 1.0f };
		float AmbientIntensity { 0.0f };
		float DiffuseIntensity { 1.0f };
		glm::vec3 Direction { 1000.f, 500.f, -50.0f };
	};

	class Light {
	private:
		DirectionalLight lightData;
	public:
		Light(Shader& shader) {
			shader.SetUniform1f("gDirectionalLight.AmbientIntensity", lightData.AmbientIntensity);
			shader.SetUniform4f("gDirectionalLight.Color", 1.0f, 0.0f, 1.0f, 1.0f);
			shader.SetUniform1f("gDirectionalLight.DiffuseIntensity", 0.0f);
			lightData.Direction = normalize(lightData.Direction);
			float x = lightData.Direction.x;
			float y = lightData.Direction.y;
			float z = lightData.Direction.z;
			shader.SetUniform3f("gDirectionalLight.Direction", x, y, z);
		};
	};
};

#pragma once

#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace My_OpenGL {
	class Scene
	{
	public: 
		Camera camera;
	private:
			glm::mat4 proj = glm::ortho(0.f, 1920.0f, 0.f, 1080.0f, -1000.0f, 1000.0f);
			/*
				 | 1, 0, 0, Vx|
				 | 0, 1, 0, Vy|
				 | 0, 0, 1, Vz|
				 | 0, 0, 0, 1 |
			*/
			
	public:
			void calculateAndSet(double& time, glm::mat4& model, Shader& shader) const;
			void setView(glm::mat4& model, Shader& shader) const;
	};
};
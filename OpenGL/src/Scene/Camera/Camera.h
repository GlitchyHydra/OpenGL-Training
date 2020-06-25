#pragma once

#include "glm/vec3.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

namespace My_OpenGL {
	class Camera
	{
	public:
		bool setted = false;
		glm::vec3 positionNext{ 0.0f, 0.0f, 0.0f };
		glm::vec3 position {0.0f, 0.0f, 0.0f};
		mutable glm::vec3 offset{ 0.0f, 0.0f, 0.0f };
		float lastX = 960, lastY = 540, yaw = 0.0f, pitch = 0.0f;
		mutable glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
		float step = 1000.0f;

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	private:
		float radius = 300.0f;
		/*
					|Rx Ry Rz 0|   |1 0 0 -Px|   |Rx Ry Rz -(Rx * Px + Ry * Py + Rz * Pz)|
		LookAt =	|Ux Uy Uz 0| * |0 1 0 -Py| = |Ux Uy Uz -(Ux * Px + Uy * Py + Uz * Pz)|
					|Dx Dy Dz 0|   |0 0 1 -Pz|   |Dx Dy Dz -(Dx * Px + Dy * Py + Dz * Pz)|
					|0  0  0  1|   |0 0 0  1 |   |0  0  0    1                           |

		*/
		mutable glm::mat4 view = glm::lookAt(position,
										     target,
									         glm::vec3(0.0f, 1.0f, 0.0f));
	public:
		glm::mat4& GetView() const;
		void Print() const;
		void SetEyeInShader(Shader& shader) const;

		void Right() { this->position.x -= 10; }
		void Left() { this->position.x += 10; }
		void Up() { this->position.y -= 10; };
		void Down() { this->position.y += 10; };
		void Forward();
		void Back();
	};
};
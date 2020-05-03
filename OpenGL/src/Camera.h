#pragma once

#include "glm/vec3.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace My_OpenGL {
	class Camera
	{
	public:
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	private:
		float radius = 300.0f;
		mutable float camX = 0.0f;
		mutable float camZ = 0.0f;
		glm::vec3 target = { 1000.f, 500.f, 10.f };
		glm::vec3 direction = glm::normalize(position - target);
		glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
		glm::vec3 up = glm::normalize(glm::cross(direction, right));
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
		glm::mat4& GetView(double& time) const;
		glm::mat4& GetView() const;
	};
};
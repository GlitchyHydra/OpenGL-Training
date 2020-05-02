#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace My_OpenGL {
	class Scene
	{
		private:
			glm::mat4 proj = glm::ortho(0.f, 1920.0f, 0.f, 1080.0f, -100.0f, 100.0f);
			/*
				 | 1, 0, 0, Vx|
				 | 0, 1, 0, Vy|
				 | 0, 0, 1, Vz|
				 | 0, 0, 0, 1 |
			*/
			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
		public:
			void calculateAndSet(glm::mat4& model, Shader& shader) const;
	};
};
#include "Camera.h"

namespace My_OpenGL {

	glm::mat4& My_OpenGL::Camera::GetView() const
	{
		return view;
	}

	glm::mat4& My_OpenGL::Camera::GetView(double& time) const
	{
		camX = abs(sin(time) * radius);
		camZ = abs(cos(time) * radius);
		view = glm::lookAt(glm::vec3(camX, 0.0, camZ),
			glm::vec3(0.0f, 0.0f, 0.0),
			glm::vec3(0.0f, 1.0f, 0.0));
		return view;
	}
}

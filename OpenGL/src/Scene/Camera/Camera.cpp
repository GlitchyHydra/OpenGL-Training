#include "Camera.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace My_OpenGL {

	glm::mat4& Camera::GetView() const
	{
        if (setted)
        std::cout << positionNext.x << std::endl;
        view = glm::lookAt(position,
                           position + target,
                           up);
		return view;
	}

    void Camera::SetEyeInShader(Shader& shader) const
    {
        glm::vec3 eye = position + target;
        shader.SetUniform3f("u_CameraPos", eye.x, eye.y, eye.z);
    }

    glm::mat4 myLookAt(const glm::vec3& target, const glm::vec3& up)
    {
        glm::vec3 target_n = normalize(target);
        glm::vec3 up_n = normalize(up);
        return glm::mat4();
    }
}

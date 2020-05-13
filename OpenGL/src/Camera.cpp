#include "Camera.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace My_OpenGL {

	glm::mat4& Camera::GetView() const
	{
        view = glm::lookAt(position,
                           position + target,
                           up);
		return view;
	}

    void Camera::SetEyeInShader(Shader& shader) const
    {
        glm::vec3 eye = position + target;
        shader.SetUniform3f("gEyeWorldPos", eye.x, eye.y, eye.z);
    }

    bool Camera::OnKeyboard(int key) 
    {
        bool ret = false;
        switch (key) {
            case GLFW_KEY_W: {
                position += (target * step);
                ret = true;
            } break;

            case GLFW_KEY_S: {
                position -= (target * step);
                ret = true;
            } break;

            case GLFW_KEY_A: {
                position -= glm::normalize(glm::cross(target, up)) * step;
                ret = true;
            } break;

            case GLFW_KEY_D: {
                position += glm::normalize(glm::cross(target, up)) * step;;
                ret = true;
            } break;

        }

        return ret;
    }

    void Camera::OnMouse(const double xpos, const double ypos)
    {
       
        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        GLfloat sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        target = glm::normalize(front);
    }

    void Camera::Print() const
    {
        std::cout << view[0][0] << "\t";
        std::cout << view[0][1] << "\t";
        std::cout << view[0][2] << "\t";
        std::cout << view[0][3] << std::endl;

        std::cout << view[1][0] << "\t";
        std::cout << view[1][1] << "\t";
        std::cout << view[1][2] << "\t";
        std::cout << view[1][3] << std::endl;

        std::cout << view[2][0] << "\t";
        std::cout << view[2][1] << "\t";
        std::cout << view[2][2] << "\t";
        std::cout << view[2][3] << std::endl;

        std::cout << view[3][0] << "\t";
        std::cout << view[3][1] << "\t";
        std::cout << view[3][2] << "\t";
        std::cout << view[3][3] << std::endl;
    }

    glm::mat4 myLookAt(const glm::vec3& target, const glm::vec3& up)
    {
        glm::vec3 target_n = normalize(target);
        glm::vec3 up_n = normalize(up);
        return glm::mat4();
    }
}

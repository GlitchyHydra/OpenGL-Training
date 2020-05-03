#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "models/Scene.h"

static My_OpenGL::Scene scene;

namespace My_OpenGL{
	class Config {
		private:
			GLFWwindow* window;
			float width = 1920;
			float height = 1080;
			
		public:
			Config();
		   ~Config();

		   GLFWwindow* GetWindow() const;
	};
};
#pragma once

#include <string>

#include <imgui.h>

#include "ImGUI/ImGuiLayer.h"
#include "Scene/Scene.h"
#include "abstractions/OpenGLFramebuffer.h"

namespace My_OpenGL {

	class ImGuiViewportLayer : public ImGuiLayer
	{
	private:
		mutable ImVec2 size;
		Scene* mScene;
		OpenGLFramebuffer* mFramebuffer;

		mutable bool show;
	public:
		ImGuiViewportLayer(Scene* pScene, OpenGLFramebuffer* fbuffer);
		~ImGuiViewportLayer();

		void Begin() const override;
		void Render() const override;
	};
}
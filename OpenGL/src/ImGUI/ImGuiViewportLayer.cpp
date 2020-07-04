#include "ImGuiViewportLayer.h"


#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace My_OpenGL {

	ImGuiViewportLayer::ImGuiViewportLayer(Scene* pScene, OpenGLFramebuffer* fbuffer)
		: ImGuiLayer("Viewport")
	{
		mScene = pScene;
		mFramebuffer = fbuffer;
		size.x = mFramebuffer->GetSpecification().Width;
		size.y = mFramebuffer->GetSpecification().Height;
		show = true;
	}

	ImGuiViewportLayer::~ImGuiViewportLayer()
	{
		
	}

	void ImGuiViewportLayer::Begin() const
	{
		ImGui::Begin(GetName().c_str(), &show,
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	}

	void ImGuiViewportLayer::Render() const
	{
		if (size.x != ImGui::GetWindowWidth() || size.y != ImGui::GetWindowHeight())
		{
			size.x = ImGui::GetWindowWidth();
			size.y = ImGui::GetWindowHeight();
			mFramebuffer->SetNewParametrs(size.x, size.y);
		}
		auto tex = mFramebuffer->GetColorAttachmentTexID();
		
		ImGui::Image((void*)tex, size);
	}
}
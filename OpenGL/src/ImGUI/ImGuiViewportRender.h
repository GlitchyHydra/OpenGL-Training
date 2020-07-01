#pragma once

namespace My_OpenGL {

	class ImGuiViewportRender
	{
	public:
		ImGuiViewportRender();
		~ImGuiViewportRender();

		void Begin();
		void Render();
		void End();
	};
}
#pragma once
#include "../Core/API/Defines.h"
#include "../../ThirdParty/imgui/imgui.h"
#include "../../ThirdParty/imgui/backends/imgui_impl_opengl3.h"
#include "../../ThirdParty/imgui/backends/imgui_impl_glfw.h"

namespace UVKEditor
{
	void ShowStatisticsPanel()
	{
		ImGui::Begin("Statistics");

#ifdef Legacy
		ImGui::Text("OpenGL average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
#else
		ImGui::Text("Vulkan average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
#endif

		ImGui::End();
	}
}
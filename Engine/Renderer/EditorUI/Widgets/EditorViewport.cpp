// EditorViewport.cpp
// Last update 15/5/2021 by Madman10K
#include <GL/glew.h>
#include "EditorViewport.hpp"
#include <imgui.h>

void EditorViewport::display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight, bool& bShow)
{
    ImGui::Begin("Viewport##1", &bShow);

    if (viewportWidth != (int)ImGui::GetWindowWidth() || viewportHeight != (int)ImGui::GetWindowHeight())
    {
        UVK::GLFrameBuffer::unbindFramebuffer();
        fb.destroyFramebuffer();

        glViewport(0, 0, (int)ImGui::GetWindowWidth(), (int)ImGui::GetWindowHeight());
        fb.init((int)ImGui::GetWindowWidth(), (int)ImGui::GetWindowHeight());
        viewportWidth = (int)ImGui::GetWindowWidth();
        viewportHeight = (int)ImGui::GetWindowHeight();
    }
    ImGui::Image((void*)(intptr_t)fb.getFramebufferTexture(), ImVec2((float)viewportWidth, (float)viewportHeight), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}
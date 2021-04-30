// EditorViewport.hpp
// Last update 4/24/2021 by Madman10K
#pragma once
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>
#include "Engine/Renderer/OpenGL/Components/GLFrameBuffer.hpp"

namespace EditorViewport
{
    static void display(UVK::GLFrameBuffer& fb, int& viewportWidth, int& viewportHeight)
    {
        ImGui::Begin("Viewport##1");

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
}
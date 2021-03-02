// Statistics.hpp
// Last update 3/2/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace Statistics
{
    // Displays statistics
    static void display()
    {
        ImGui::Begin("Statistics");

        ImGui::Text("Performance: %.3f ms(%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }
}
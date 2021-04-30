// WorldSettings.hpp
// Last update 4/12/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace WorldSettings
{
    // Displays the world setting widget
    static void display(UVK::FVector4& colour, UVK::FVector4 ambientLight, std::string& name)
    {
        ImGui::Begin("World Settings");

        ImGui::InputText("Level Name", &name);

        ImGui::ColorEdit4("Colour background", (float*)&colour);
        ImGui::ColorEdit4("Ambient Light", (float*)&ambientLight); // W is for ambient light intensity

        ImGui::End();
    }
}
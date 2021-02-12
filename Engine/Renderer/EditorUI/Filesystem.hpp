// Filesystem.hpp
// Last update 2/12/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Textures/Texture.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace Filesystem
{
    static void display(UVK::Texture& folder, UVK::Texture& audio)
    {
        ImGui::Begin("File System");

#ifndef __MINGW__
        for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::path("Content")))
        {
            ImGui::BeginGroup();

            if (entry.is_directory())
            {
                ImGui::Image((void*)(intptr_t)folder.getImage(), ImVec2(folder.getWidth() - 1500, folder.getHeight() - 1500));
            }
            else if (entry.path().extension() == ".wav")
            {
                ImGui::Image((void*)(intptr_t)audio.getImage(), ImVec2(audio.getWidth() - 410, audio.getHeight() - 410));
            }
            ImGui::Text("%s", entry.path().c_str());
            ImGui::EndGroup();
#endif
            ImGui::SameLine();
        }

        ImGui::End();
    }
}
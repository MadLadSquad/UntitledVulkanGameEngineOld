// Filesystem.hpp
// Last update 2/24/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Textures/Texture.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace Filesystem
{
    static void display(UVK::Texture& folder, UVK::Texture& audio, UVK::Texture& model)
    {
        ImGui::Begin("File System");

#ifndef __MINGW32__
        for (const auto& entry : std_filesystem::directory_iterator(std_filesystem::path("../Content")))
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
            else if (entry.path().extension() == ".obj" || entry.path().extension() == ".fbx")
            {
                ImGui::Image((void*)(intptr_t)model.getImage(), ImVec2(model.getWidth() - 410, model.getHeight() - 410));
            }

            ImGui::Text("%s", utility.sanitiseFilepath(entry.path().filename().string(), true)); 
            
            ImGui::EndGroup();

            ImGui::SameLine();
        }
#endif
        ImGui::End();
    }
}
// Filesystem.hpp
// Last update 4/28/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "Engine/Renderer/Textures/Texture.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>
#ifndef __MINGW32__
namespace Filesystem
{
    // filesystem widget
    static void display(UVK::Texture& folder, UVK::Texture& audio, UVK::Texture& model, std_filesystem::path& pt)
    {
        ImGui::Begin("File System");


        for (const auto& entry : std_filesystem::directory_iterator(pt))
        {
            ///bool directory = false;
            std::string path = entry.path().filename().string();
            Utility::sanitiseFilepath(path, true);
            ImTextureID txt = nullptr;
            ImVec2 dm;

            ImGui::BeginGroup();
            if (entry.is_directory())
            {
                //directory = true;
                txt = (void*)(intptr_t)folder.getImage();
                dm = ImVec2((float)folder.getWidth() - 1500, (float)folder.getHeight() - 1500);
            }
            else if (entry.path().extension() == ".wav")
            {
                txt = (void*)(intptr_t)audio.getImage();
                dm = ImVec2((float)audio.getWidth() - 410, (float)audio.getHeight() - 410);
            }
            else if (entry.path().extension() == ".obj" || entry.path().extension() == ".fbx")
            {
                txt = (void*)(intptr_t)model.getImage(); 
                dm = ImVec2((float)model.getWidth() - 410, (float)model.getHeight() - 410);
            }
            else
            {
                //txt = (void*)(intptr_t)model.getImage();
                //dm = ImVec2((float)model.getWidth() - 410, (float)model.getHeight() - 410);
            }
            if (ImGui::ImageButton(txt, dm))
            {
                pt = std_filesystem::path(static_cast<std::string>(pt.string() + entry.path().filename().string()));
            }
            ImGui::Text("%s", path);

            ImGui::EndGroup();

            ImGui::SameLine();
        }

        ImGui::End();
    }
}
#endif
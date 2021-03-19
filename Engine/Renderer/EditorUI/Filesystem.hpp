// Filesystem.hpp
// Last update 3/17/2021 by Madman10K
#pragma once
#include <Core.hpp>
#include "../Textures/Texture.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <cpp/imgui_stdlib.h>

namespace Filesystem
{
    // filesystem widget
    static void display(UVK::Texture& folder, UVK::Texture& audio, UVK::Texture& model)
    {
        ImGui::Begin("File System");
#ifndef __MINGW32__
        std_filesystem::path pt("../Content");


        for (const auto& entry : std_filesystem::directory_iterator(pt))
        {
            bool directory = false;
            std::string path = entry.path().filename().string();
            utility.sanitiseFilepath(path, true);
            ImTextureID txt = 0;
            ImVec2 dm;

            ImGui::BeginGroup();
            if (entry.is_directory())
            {
                directory = true;
                txt = (void*)(intptr_t)folder.getImage();
                dm = ImVec2(folder.getWidth() - 1500, folder.getHeight() - 1500);
            }
            else if (entry.path().extension() == ".wav")
            {
                txt = (void*)(intptr_t)audio.getImage();
                dm = ImVec2(audio.getWidth() - 410, audio.getHeight() - 410);
            }
            else if (entry.path().extension() == ".obj" || entry.path().extension() == ".fbx")
            {
                txt = (void*)(intptr_t)model.getImage(); 
                dm = ImVec2(model.getWidth() - 410, model.getHeight() - 410);
            }
            
            if (ImGui::ImageButton(txt, dm) && directory)
            {
                pt = std_filesystem::path(entry.path().filename().string());
            }
            ImGui::Text("%s", path);

            ImGui::EndGroup();

            ImGui::SameLine();
        }
#endif
        ImGui::End();
    }
}
// TopToolbar.hpp
// Last update 4/24/2021 by Madman10K
#pragma once
#include "Engine/Renderer/Textures/Texture.hpp"

namespace TopToolbar
{
    static void display(UVK::Texture& play)
    {
        int lnt = 0;

        ImGui::Begin("Toolbar");

        if (ImGui::ImageButton((void*)(intptr_t)play.getImage(), ImVec2((float)play.getWidth(), (float)play.getHeight())))
        {
#ifdef _WIN32
            lnt = system("Game.exe");
#else
            lnt = system("./Game");
#endif
        }

        if (lnt)
        {

        }

        ImGui::End();
    }
}

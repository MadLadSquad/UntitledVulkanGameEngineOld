// TopToolbar.cpp
// Last update 15/6/2021 by Madman10K
#include "TopToolbar.hpp"
#include <imgui.h>

#ifndef PRODUCTION
void TopToolbar::display(UVK::Texture &play, bool& bShow)
{
    int lnt = 0;

    ImGui::Begin("Toolbar", &bShow);

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
#endif
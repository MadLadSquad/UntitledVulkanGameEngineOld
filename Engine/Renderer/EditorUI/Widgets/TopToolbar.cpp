// TopToolbar.cpp
// Last update 5/5/2021 by Madman10K
#include "TopToolbar.hpp"
#include <imgui.h>

void TopToolbar::display(UVK::Texture &play)
{
    int lnt = 0;

    ImGui::Begin("Toolbar", nullptr);

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
// TopToolbar.cpp
// Last update 13/9/2021 by Madman10K
#include "TopToolbar.hpp"
#include <imgui.h>

#ifndef PRODUCTION
void TopToolbar::display(UVK::Texture &play, const std::string& projectName, bool& bShow)
{
    int8_t lnt = 0;

    ImGui::Begin("Toolbar", &bShow);

    if (ImGui::ImageButton((void*)(intptr_t)play.getImage(), ImVec2((float)50, (float)50), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), 0))
    {
#ifdef _WIN32
        lnt = system(static_cast<std::string>(projectName + ".exe").c_str());
#else
        lnt = system(static_cast<std::string>("./" + projectName).c_str());
#endif
    }

    if (lnt)
    {

    }

    ImGui::End();
}
#endif
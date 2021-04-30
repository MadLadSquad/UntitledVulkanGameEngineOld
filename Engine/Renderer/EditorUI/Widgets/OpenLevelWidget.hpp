// OpenLevelWidget.hpp
// Last update 4/24/2021 by Madman10K
#pragma once
#include <imgui.h>
#include <iostream>

namespace OpenLevelWidget
{
    static void display(std::string& openLevel, bool& bShowOpenLevelWidget)
    {
        ImGui::Begin("Open Level");

        ImGui::InputText("File location", &openLevel);

        ImGui::Text("Keep in mind that clicking Submit WILL NOT SAVE any changes made to the level you are editing");
        if (ImGui::Button("Cancel"))
        {
            bShowOpenLevelWidget = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Submit"))
        {
            UVK::Level::open(openLevel.c_str());
            bShowOpenLevelWidget = false;
        }

        ImGui::End();
    }
}
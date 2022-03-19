// NewLevel.cpp
// Last update 18/2/2022 by Madman10K
#include "NewLevel.hpp"
#ifndef PRODUCTION
#include "Core/Actor.hpp"

void NewLevel::display(bool &bShow)
{
    if (!ImGui::IsPopupOpen("WARNING##new level"))
        ImGui::OpenPopup("WARNING##new level");
    if (ImGui::BeginPopupModal("WARNING##new level", &bShow))
    {
        ImGui::TextWrapped("Creating a new level will not save any changes to the level you are currently editing!");
        ImGui::TextWrapped("If you want to save your changes click Cancel and do so, otherwise you can click Create");

        if (ImGui::Button("Cancel"))
            bShow = false;

        ImGui::SameLine();

        if (ImGui::Button("Create##new level"))
        {
            UVK::ECS::clear();
            bShow = false;
        }
        ImGui::EndPopup();
    }
}
#endif
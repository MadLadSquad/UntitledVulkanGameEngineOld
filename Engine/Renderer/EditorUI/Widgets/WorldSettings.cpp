// WorldSettings.cpp
// Last update 1/8/2021 by Madman10K
#include "WorldSettings.hpp"

#ifndef PRODUCTION
void WorldSettings::display(UVK::FVector4& colour, UVK::FVector4& ambientLight, std::string& name, bool& bShow)
{
    ImGui::Begin("World Settings", &bShow);

    ImGui::TextWrapped("Level name");
    ImGui::SameLine();
    ImGui::InputText("##Level Name ln", &name);

    ImGui::TextWrapped("Colour background");
    ImGui::SameLine();
    ImGui::ColorEdit4("##Colour background cb", (float*)&colour);

    ImGui::TextWrapped("Ambient Light");
    ImGui::SameLine();
    ImGui::ColorEdit4("##Ambient Light al", (float*)&ambientLight); // W is for ambient light intensity

    ImGui::End();
}
#endif
// WorldSettings.cpp
// Last update 15/6/2021 by Madman10K
#include "WorldSettings.hpp"

#ifndef PRODUCTION
void WorldSettings::display(UVK::FVector4& colour, UVK::FVector4& ambientLight, std::string& name, bool& bShow)
{
    ImGui::Begin("World Settings", &bShow);

    ImGui::InputText("Level Name", &name);

    ImGui::ColorEdit4("Colour background", (float*)&colour);
    ImGui::ColorEdit4("Ambient Light", (float*)&ambientLight); // W is for ambient light intensity

    ImGui::End();
}
#endif
#include "WorldSettings.hpp"

#ifndef PRODUCTION
bool WorldSettings::display(UVK::FVector4& colour, UVK::FVector4& ambientLight, UVK::FString& name, bool& bShow) noexcept
{
    bool bReturn = false;
    ImGui::Begin("World Settings", &bShow);

    ImGui::TextWrapped("Level name");
    ImGui::SameLine();
    if (ImGui::InputText("##Level Name ln", &name) || ImGui::IsItemActive())
        bReturn = true;

    ImGui::TextWrapped("Colour background");
    ImGui::SameLine();
    ImGui::ColorEdit4("##Colour background cb", (float*)&colour);

    ImGui::TextWrapped("Ambient Light");
    ImGui::SameLine();
    ImGui::ColorEdit4("##Ambient Light al", (float*)&ambientLight); // W is for ambient light intensity

    ImGui::End();
    return bReturn;
}
#endif
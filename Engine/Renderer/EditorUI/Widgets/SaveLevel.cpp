// SaveLevel.cpp
// Last update 1/8/2021 by Madman10K
#include "SaveLevel.hpp"
#ifndef PRODUCTION
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"

bool SaveLevel::display(bool &bOpen, std::string& location, UVK::FVector4& colour)
{
    bool bReturn = false;
    if (!ImGui::IsPopupOpen("Save level"))
        ImGui::OpenPopup("Save level");

    if (ImGui::BeginPopupModal("Save level", &bOpen))
    {
        ImGui::TextWrapped("Location: Content/");
        ImGui::SameLine();
        if (ImGui::InputText("##location##inputlocationsave", &location) || ImGui::IsItemFocused())
            bReturn = true;
        ImGui::SameLine();
        ImGui::TextWrapped(".uvklevel");

        if (ImGui::Button("Cancel##cancelbuttononsave"))
        {
            bOpen = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Submit##submitbuttononsave"))
        {
            std::string temp = "../Content/" + location;
            UVK::Level::save(temp.c_str());
            bOpen = false;
        }

        ImGui::EndPopup();
    }
    return bReturn;
}
#endif
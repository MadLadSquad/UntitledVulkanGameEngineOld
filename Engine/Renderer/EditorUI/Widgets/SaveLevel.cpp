// SaveLevel.cpp
// Last update 1/8/2021 by Madman10K
#include <GL/glew.h>
#include "SaveLevel.hpp"
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"

#ifndef PRODUCTION
void SaveLevel::display(bool &bOpen, std::string& location, UVK::FVector4& colour)
{
    if (!ImGui::IsPopupOpen("Save level"))
        ImGui::OpenPopup("Save level");

    if (ImGui::BeginPopupModal("Save level", &bOpen))
    {
        ImGui::TextWrapped("Location: Content/");
        ImGui::SameLine();
        ImGui::InputText("##location##inputlocationsave", &location);
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
}
#endif
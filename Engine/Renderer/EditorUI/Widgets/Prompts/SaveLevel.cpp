#include "SaveLevel.hpp"
#ifndef PRODUCTION
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"

bool SaveLevel::display(bool &bOpen, std::string& location, UVK::FVector4& colour) noexcept
{
    bool bReturn = false;
    if (!ImGui::IsPopupOpen("Save level"))
        ImGui::OpenPopup("Save level");

    if (ImGui::BeginPopupModal("Save level", &bOpen))
    {
        ImGui::TextWrapped("Location: Content/");
        ImGui::SameLine();
        if (ImGui::InputText("##location##inputlocationsave", &location) || ImGui::IsItemActive())
            bReturn = true;
        ImGui::SameLine();
        ImGui::TextWrapped(".uvklevel");

        if (ImGui::Button("Cancel##cancelbuttononsave"))
            bOpen = false;

        ImGui::SameLine();

        if (ImGui::Button("Submit##submitbuttononsave"))
        {
            std::string temp = UVK_CONTENT_PATH + location;
            UVK::Level::save(temp.c_str());
            bOpen = false;
        }

        ImGui::EndPopup();
    }
    return bReturn;
}
#endif
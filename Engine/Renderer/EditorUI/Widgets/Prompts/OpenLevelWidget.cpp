// OpenLevelWidget.cpp
// Last update 18/2/2022 by Madman10K
#include "OpenLevelWidget.hpp"
#ifndef PRODUCTION
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <Renderer/EditorUI/Classes/EditorLevel.hpp>

bool OpenLevelWidget::display(std::string &openLevel, bool &bShowOpenLevelWidget, double& dr, UVK::FVector4& colour)
{
    bool bReturn = false;
    if (!ImGui::IsPopupOpen("Open Level"))
        ImGui::OpenPopup("Open Level");
    if (ImGui::BeginPopupModal("Open Level", &bShowOpenLevelWidget))
    {
        ImGui::TextWrapped("File location: Content/");
        ImGui::SameLine();
        if (ImGui::InputText("##File location", &openLevel) || ImGui::IsItemActive())
            bReturn = true;
        ImGui::SameLine();
        ImGui::TextWrapped(".uvklevel");

        ImGui::TextWrapped("Keep in mind that clicking Submit WILL NOT SAVE any changes made to the level you are editing");
        if (ImGui::Button("Cancel"))
            bShowOpenLevelWidget = false;

        ImGui::SameLine();

        if (ImGui::Button("Submit"))
        {
            Timer tm;
            tm.startRecording();

            auto loc = "../Content/" + openLevel;
            UVK::Level::open<UVK::EditorLevel>(loc);

            tm.stopRecording();
            dr = tm.getDuration();

            bShowOpenLevelWidget = false;
        }

        ImGui::EndPopup();
    }
    return bReturn;
}
#endif
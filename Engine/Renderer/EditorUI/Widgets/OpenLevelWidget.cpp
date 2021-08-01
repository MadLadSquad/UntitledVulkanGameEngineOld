// OpenLevelWidget.cpp
// Last update 1/8/2021 by Madman10K
#include <GL/glew.h>
#include "OpenLevelWidget.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>
#include <Renderer/EditorUI/Classes/EditorLevel.hpp>

#ifndef PRODUCTION
void OpenLevelWidget::display(std::string &openLevel, bool &bShowOpenLevelWidget, double& dr, UVK::FVector4& colour)
{
    if (!ImGui::IsPopupOpen("Open Level"))
        ImGui::OpenPopup("Open Level");
    if (ImGui::BeginPopupModal("Open Level", &bShowOpenLevelWidget))
    {
        ImGui::TextWrapped("File location: Content/");
        ImGui::SameLine();
        ImGui::InputText("##File location", &openLevel);
        ImGui::SameLine();
        ImGui::TextWrapped(".uvklevel");

        ImGui::TextWrapped("Keep in mind that clicking Submit WILL NOT SAVE any changes made to the level you are editing");
        if (ImGui::Button("Cancel"))
        {
            bShowOpenLevelWidget = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Submit"))
        {
            Timer tm;
            tm.startRecording();

            UVK::Level::open<UVK::EditorLevel>(static_cast<std::string>("Content/" + openLevel).c_str());

            tm.stopRecording();
            dr = tm.getDuration();

            bShowOpenLevelWidget = false;
        }

        ImGui::EndPopup();
    }
}
#endif
// OpenLevelWidget.cpp
// Last update 2/7/2021 by Madman10K
#include <GL/glew.h>
#include "OpenLevelWidget.hpp"
#include "../../GameFramework/GameplayClasses/Level/Level.hpp"
#include <imgui.h>
#include <cpp/imgui_stdlib.h>

#ifndef PRODUCTION
void OpenLevelWidget::display(std::string &openLevel, bool &bShowOpenLevelWidget, double& dr, UVK::FVector4& colour, std::string& name, UVK::Texture& insert, const std::string& cpFileLoc)
{
    ImGui::Begin("Open Level", &bShowOpenLevelWidget);

    ImGui::InputTextWithHint("File location", "Location starts from the content folder", &openLevel);
    ImGui::SameLine();
    if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.0f, 10.0f)))
    {
        openLevel = cpFileLoc;
    }

    ImGui::Text("Keep in mind that clicking Submit WILL NOT SAVE any changes made to the level you are editing");
    if (ImGui::Button("Cancel"))
    {
        bShowOpenLevelWidget = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Submit"))
    {
        Timer tm;
        tm.startRecording();

        UVK::Level::open(static_cast<std::string>("Content/" + openLevel).c_str());

        tm.stopRecording();
        dr = tm.getDuration();

        bShowOpenLevelWidget = false;
    }

    ImGui::End();
}
#endif
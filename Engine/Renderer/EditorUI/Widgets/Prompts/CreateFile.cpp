// CreateFile.cpp
// Last update 18/2/2022 by Madman10K
#include "CreateFile.hpp"
#ifndef PRODUCTION
#include <cpp/imgui_stdlib.h>
#include <UVKBuildTool/src/FileGenerator.hpp>

bool CreateFile::display(std::string& fileOutLocation, bool& bShowCreateFile1, const std::string& prjname)
{
    bool bReturn = false;
    if (!ImGui::IsPopupOpen("Create a file"))
        ImGui::OpenPopup("Create a file");

    if (ImGui::BeginPopupModal("Create a file", &bShowCreateFile1))
    {
        static std::string str;
        static std::string sf;
        ImGui::Columns(2, nullptr, false);

        ImGui::TextWrapped("File type");
        ImGui::SameLine();
        if (ImGui::BeginCombo("##FileType", str.c_str()))
        {
            if (ImGui::MenuItem("Game mode"))
            {
                sf = "UVK::GameMode";
                str = "Game mode";
            }

            if (ImGui::MenuItem("Game state"))
            {
                sf = "UVK::GameState";
                str = "Game state";
            }

            if (ImGui::MenuItem("Player state"))
            {
                sf = "UVK::PlayerState";
                str = "Player state";
            }

            if (ImGui::MenuItem("Player controller"))
            {
                sf = "UVK::PlayerController";
                str = "Player controller";
            }

            if (ImGui::MenuItem("Pawn"))
            {
                sf = "UVK::Pawn";
                str = "Pawn";
            }

            if (ImGui::MenuItem("Level"))
            {
                sf = "UVK::Level";
                str = "Level";
            }

            if (ImGui::MenuItem("Scriptable object"))
            {
                sf = "UVK::ScriptableObject";
                str = "Scriptable object";
            }

            ImGui::EndCombo();
        }

        ImGui::Columns(1);
        ImGui::Text("Selected file type: %s", str.c_str());
        ImGui::TextWrapped("Location: Source/");
        ImGui::SameLine();
        if (ImGui::InputText("##Location##genfile", &fileOutLocation) || ImGui::IsItemActive())
            bReturn = true;

        if (ImGui::Button("Cancel"))
        {
            sf = "";
            bShowCreateFile1 = false;
            fileOutLocation = "";
        }

        ImGui::SameLine();

        if (ImGui::Button("Create"))
        {
            UBT::makeTemplate(fileOutLocation, sf, prjname.c_str());

            bShowCreateFile1 = false;
            fileOutLocation = "";
            sf = "";
        }

        ImGui::EndPopup();
    }
    return bReturn;
}
#endif
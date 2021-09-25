// CreateFile.cpp
// Last update 12/9/2021 by Madman10K
#include "CreateFile.hpp"
#include <cpp/imgui_stdlib.h>
#include <Core.hpp>

#ifndef PRODUCTION
void CreateFile::display(std::string& fileOutLocation, bool& bShowCreateFile1)
{
    if (!ImGui::IsPopupOpen("Create a file"))
        ImGui::OpenPopup("Create a file");

    if (ImGui::BeginPopupModal("Create a file", &bShowCreateFile1))
    {
        static std::string str;
        static int sf = 0;
        ImGui::Columns(2, nullptr, false);

        ImGui::TextWrapped("File type");
        ImGui::SameLine();
        if (ImGui::BeginCombo("##FileType", str.c_str()))
        {
            if (ImGui::MenuItem("Game mode"))
            {
                sf = 1;
                str = "Game mode";
            }

            if (ImGui::MenuItem("Game state"))
            {
                sf = 2;
                str = "Game state";
            }

            if (ImGui::MenuItem("Player state"))
            {
                sf = 3;
                str = "Player state";
            }

            if (ImGui::MenuItem("Player controller"))
            {
                sf = 4;
                str = "Player controller";
            }

            if (ImGui::MenuItem("Pawn"))
            {
                sf = 5;
                str = "Pawn";
            }

            if (ImGui::MenuItem("Level"))
            {
                sf = 6;
                str = "Level";
            }

            if (ImGui::MenuItem("Scriptable object"))
            {
                sf = 7;
                str = "Scriptable object";
            }

            ImGui::EndCombo();
        }

        ImGui::Columns(1);
        ImGui::Text("Selected file type: %s", str.c_str());
        ImGui::TextWrapped("Location: Source/");
        ImGui::SameLine();
        ImGui::InputText("##Location##genfile", &fileOutLocation);

        if (ImGui::Button("Cancel"))
        {
            sf = 0;
            bShowCreateFile1 = false;
            fileOutLocation = "";
        }

        ImGui::SameLine();

        if (ImGui::Button("Create"))
        {
            std::string gen;
            switch (sf)
            {
#ifdef _WIN32
            case 1:
                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --game-mode " + fileOutLocation + " && cd ../../";
                break;
            case 2:
                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --game-state " + fileOutLocation + " && cd ../../";
                break;
            case 3:
                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --player-state " + fileOutLocation + " && cd ../../";
                break;
            case 4:
                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --player-controller " + fileOutLocation + " && cd ../../";
                break;
            case 5:
                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --pawn " + fileOutLocation + " && cd ../../";
                break;
            case 6:
                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --level " + fileOutLocation + " && cd ../../";
                break;
            case 7:
                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --scriptable-object " + fileOutLocation + " --add && cd ../../";
                break;
#else
                case 1:
                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --game-mode " + fileOutLocation + " && cd ../../";
                    break;
                case 2:
                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --game-state " + fileOutLocation + " && cd ../../";
                    break;
                case 3:
                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --player-state " + fileOutLocation + " && cd ../../";
                    break;
                case 4:
                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --player-controller " + fileOutLocation + " && cd ../../";
                    break;
                case 5:
                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --pawn " + fileOutLocation + " && cd ../../";
                    break;
                case 6:
                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --level " + fileOutLocation + " && cd ../../";
                    break;
                case 7:
                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --scriptable-object " + fileOutLocation + " --add && cd ../../";
                    break;
#endif
                default:
                    break;
            }

            if (system(gen.c_str()))
            {
                logger.consoleLog("Error when generating files!", UVK_LOG_TYPE_ERROR);
            }

            bShowCreateFile1 = false;
            fileOutLocation = "";
            sf = 0;
        }

        ImGui::EndPopup();
    }
}
#endif
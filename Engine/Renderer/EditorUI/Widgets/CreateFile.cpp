// CreateFile.cpp
// Last update 12/8/2021 by Madman10K
#include "CreateFile.hpp"
#include <cpp/imgui_stdlib.h>
#include <Core.hpp>

#ifndef PRODUCTION
void CreateFile::display(uint8_t selectedFile, std::string& fileOutLocation, bool& bShowCreateFile1)
{
    if (!ImGui::IsPopupOpen("Create a file"))
        ImGui::OpenPopup("Create a file");

    if (ImGui::BeginPopupModal("Create a file", &bShowCreateFile1))
    {
        static std::string str;

        ImGui::Columns(2, nullptr, false);

        ImGui::TextWrapped("File type");
        ImGui::SameLine();
        if (ImGui::BeginCombo("##FileType", str.c_str()))
        {
            if (ImGui::MenuItem("Game mode"))
            {
                selectedFile = 1;
                str = "Game mode";
                goto end;
            }

            if (ImGui::MenuItem("Game state"))
            {
                selectedFile = 2;
                str = "Game state";
                goto end;
            }

            if (ImGui::MenuItem("Player state"))
            {
                selectedFile = 3;
                str = "Player state";
                goto end;
            }

            if (ImGui::MenuItem("Player controller"))
            {
                selectedFile = 4;
                str = "Player controller";
                goto end;
            }

            if (ImGui::MenuItem("Pawn"))
            {
                selectedFile = 5;
                str = "Pawn";
                goto end;
            }

            if (ImGui::MenuItem("Level"))
            {
                selectedFile = 6;
                str = "Level";
                goto end;
            }

            if (ImGui::MenuItem("Scriptable object"))
            {
                selectedFile = 7;
                str = "Scriptable object";
            }
end:

            ImGui::EndCombo();
        }

        ImGui::Columns(1);
        ImGui::Text("Selected file type: %s", str.c_str());
        ImGui::TextWrapped("Location: Source/");
        ImGui::SameLine();
        ImGui::InputText("##Location##genfile", &fileOutLocation);

        if (ImGui::Button("Cancel"))
        {
            selectedFile = 0;
            bShowCreateFile1 = false;
            fileOutLocation = "";
        }

        ImGui::SameLine();

        if (ImGui::Button("Create"))
        {
            // This is so the linter can shut up
            int lnt;
            switch (selectedFile)
            {
#ifdef _WIN32
                case 1:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --game-mode " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 2:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --game-state " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 3:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --player-state " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 4:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --player-controller " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 5:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --pawn " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 6:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --level " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 7:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --actor " + fileOutLocation + " --add && cd ../../").c_str());
                break;
#else
                case 1:
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --game-mode " + fileOutLocation + " && cd ../../").c_str());
                    break;
                case 2:
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --game-state " + fileOutLocation + " && cd ../../").c_str());
                    break;
                case 3:
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --player-state " + fileOutLocation + " && cd ../../").c_str());
                    break;
                case 4:
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --player-controller " + fileOutLocation + " && cd ../../").c_str());
                    break;
                case 5:
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --pawn " + fileOutLocation + " && cd ../../").c_str());
                    break;
                case 6:
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --level " + fileOutLocation + " && cd ../../").c_str());
                    break;
                case 7:
                    lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --actor " + fileOutLocation + " --add && cd ../../").c_str());
                    break;
#endif
                default:
                    lnt = 15;
                    break;
            }

            if (lnt)
            {
                logger.consoleLog("Error when generating files!", UVK_LOG_TYPE_ERROR);
            }

            bShowCreateFile1 = false;
            fileOutLocation = "";
        }

        ImGui::EndPopup();
    }
}
#endif
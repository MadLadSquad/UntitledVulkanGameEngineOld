// CreateFile.cpp
// Last update 20/5/2021 by Madman10K
#include "CreateFile.hpp"
#include <cpp/imgui_stdlib.h>
#include <Core.hpp>

void CreateFile::display(short& selectedFile, std::string& fileOutLocation, bool& bShowCreateFile1)
{
    ImGui::Begin("Create a file");

    // This is so the linter can shut up
    int lnt = 0;

    if (ImGui::Button("Game mode")) selectedFile = 1;
    ImGui::SameLine();
    if (ImGui::Button("Game state")) selectedFile = 2;
    ImGui::SameLine();
    if (ImGui::Button("Player state")) selectedFile = 3;
    ImGui::SameLine();
    if (ImGui::Button("Player controller")) selectedFile = 4;
    if (ImGui::Button("Pawn")) selectedFile = 5;
    ImGui::SameLine();
    if (ImGui::Button("Game instance")) selectedFile = 6;
    ImGui::SameLine();
    if (ImGui::Button("Level")) selectedFile = 7;

    ImGui::InputTextWithHint("Location##genfile", "Location starts from your Source folder!", &fileOutLocation);

    if (ImGui::Button("Create"))
    {
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
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --game-instance " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 7:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --level " + fileOutLocation + " && cd ../../").c_str());
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
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --game-instance " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 7:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --level " + fileOutLocation + " && cd ../../").c_str());
                break;
#endif
            default:
                break;
        }

        if (lnt)
        {
            logger.consoleLog("Error when generating files!", UVK_LOG_TYPE_ERROR);
        }

        selectedFile = 0;
        bShowCreateFile1 = false;
        fileOutLocation = "";
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
    {
        selectedFile = 0;
        bShowCreateFile1 = false;
        fileOutLocation = "";
    }

    ImGui::End();
}
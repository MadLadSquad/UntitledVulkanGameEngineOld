// CreateFile.cpp
// Last update 2/7/2021 by Madman10K
#include "CreateFile.hpp"
#include <cpp/imgui_stdlib.h>
#include <Core.hpp>

#ifndef PRODUCTION
void CreateFile::display(short& selectedFile, std::string& fileOutLocation, bool& bShowCreateFile1, UVK::Texture& insert, const std::string& cpFileLoc)
{
    ImGui::Begin("Create a file", &bShowCreateFile1);

    static std::string str;

    if (ImGui::Button("Game mode"))
    {
        selectedFile = 1;
        str = "Game mode";
    }
    ImGui::SameLine();
    if (ImGui::Button("Game state"))
    {
        selectedFile = 2;
        str = "Game state";
    }
    ImGui::SameLine();
    if (ImGui::Button("Player state"))
    {
        selectedFile = 3;
        str = "Player state";
    }
    ImGui::SameLine();
    if (ImGui::Button("Player controller"))
    {
        selectedFile = 4;
        str = "Player controller";
    }
    if (ImGui::Button("Pawn"))
    {
        selectedFile = 5;
        str = "Pawn";
    }
    ImGui::SameLine();
    if (ImGui::Button("Game instance"))
    {
        selectedFile = 6;
        str = "Game instance";
    }
    ImGui::SameLine();
    if (ImGui::Button("Level"))
    {
        selectedFile = 7;
        str = "Level";
    }
    ImGui::SameLine();
    if (ImGui::Button("Scriptable object"))
    {
        selectedFile = 8;
        str = "Scriptable object";
    }

    ImGui::Text("Selected file type: %s", str.c_str());

    ImGui::InputTextWithHint("Location##genfile", "Location starts from your Source folder!", &fileOutLocation);
    ImGui::SameLine();
    if (ImGui::ImageButton((void*)(intptr_t)insert.getImage(), ImVec2(10.0f, 10.0f)))
    {
        fileOutLocation = cpFileLoc;
    }

    if (ImGui::Button("Cancel"))
    {
        selectedFile = 0;
        bShowCreateFile1 = false;
        fileOutLocation = "";
    }

    ImGui::SameLine();
    static int pid;
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
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --game-instance " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 7:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && UVKBuildTool.exe --level " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 8:
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
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --game-instance " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 7:
                lnt = system(static_cast<std::string>("cd ../UVKBuildTool/build && ./UVKBuildTool --level " + fileOutLocation + " && cd ../../").c_str());
                break;
            case 8:
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

        selectedFile = 0;
        bShowCreateFile1 = false;
        fileOutLocation = "";
    }

    ImGui::End();
}
#endif
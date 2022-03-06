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
            std::string gen;
            UBT::makeTemplate(fileOutLocation, sf, prjname.c_str());

//          switch (sf)
//            {
//#ifdef _WIN32
//            case 1:
//                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --game-mode " + fileOutLocation + " && cd ../../";
//                break;
//            case 2:
//                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --game-state " + fileOutLocation + " && cd ../../";
//                break;
//            case 3:
//                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --player-state " + fileOutLocation + " && cd ../../";
//                break;
//            case 4:
//                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --player-controller " + fileOutLocation + " && cd ../../";
//                break;
//            case 5:
//                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --pawn " + fileOutLocation + " && cd ../../";
//                break;
//            case 6:
//                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --level " + fileOutLocation + " && cd ../../";
//                break;
//            case 7:
//                gen = "cd ../UVKBuildTool/build && UVKBuildTool.exe --scriptable-object " + fileOutLocation + " --add && cd ../../";
//                break;
//#else
//                case 1:
//                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --game-mode " + fileOutLocation + " && cd ../../";
//                    break;
//                case 2:
//                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --game-state " + fileOutLocation + " && cd ../../";
//                    break;
//                case 3:
//                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --player-state " + fileOutLocation + " && cd ../../";
//                    break;
//                case 4:
//                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --player-controller " + fileOutLocation + " && cd ../../";
//                    break;
//                case 5:
//                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --pawn " + fileOutLocation + " && cd ../../";
//                    break;
//                case 6:
//                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --level " + fileOutLocation + " && cd ../../";
//                    break;
//                case 7:
//                    gen = "cd ../UVKBuildTool/build && ./UVKBuildTool --scriptable-object " + fileOutLocation + " --add && cd ../../";
//                    break;
//#endif
//                case 1:
//                    UBT::makeTemplate(fileOutLocation, )
//                    break;
//                case 2:
//                    break;
//                case 3:
//                    break;
//                case 4:
//                    break;
//                case 5:
//                    break;
//                case 6:
//                    break;
//                case 7:
//                    break;
//                default:
//                    break;
//            }

//          if (system(gen.c_str()))
//          {
//              logger.consoleLog("Error when generating files!", UVK_LOG_TYPE_ERROR);
//          }

            bShowCreateFile1 = false;
            fileOutLocation = "";
            sf = "";
        }

        ImGui::EndPopup();
    }
    return bReturn;
}
#endif
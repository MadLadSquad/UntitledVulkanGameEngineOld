// Warnings.cpp
// Last update 1/8/2021 by Madman10K
#include <GL/glew.h>
#include "Warnings.hpp"
#include <imgui.h>
#include <Core/Global.hpp>
#include <GameFramework/GameplayClasses/Level/Level.hpp>

void Warnings::displayExitWarning(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("WARNING##EXITWARNING"))
        ImGui::OpenPopup("WARNING##EXITWARNING");

    if (ImGui::BeginPopupModal("WARNING##EXITWARNING", &bOpen))
    {
        ImGui::TextWrapped("WARNING: You are exiting the editor! Any changes that were not saved will not be!");
        if (ImGui::Button("Return##ed"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Exit##ed"))
        {
            bOpen = false;
            glfwSetWindowShouldClose(UVK::global.window.getWindow(), GL_TRUE);
        }

        ImGui::EndPopup();
    }
}

void Warnings::displayGenerateWarning(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("WARNING##GENERATEWARNING"))
        ImGui::OpenPopup("WARNING##GENERATEWARNING");

    if (ImGui::BeginPopupModal("WARNING##GENERATEWARNING", &bOpen))
    {
        ImGui::TextWrapped("Regenerate files?");
        if (ImGui::Button("Close##ed"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Regenerate##ed"))
        {
            bOpen = false;
            int lnt;
#ifdef _WIN32
            lnt = system("cd ../UVKBuildTool/build/ && UVKBuildTool.exe --generate && cd ../../");
#else
            lnt = system("cd ../UVKBuildTool/build/ && ./UVKBuildTool --generate && cd ../../");
#endif

            if (lnt)
            {
                logger.consoleLog("Error when regenerating files!", UVK_LOG_TYPE_ERROR, lnt);
            }
        }

        ImGui::EndPopup();
    }
}

void Warnings::displaySaveWarning(bool& bOpen)
{
    if (!ImGui::IsPopupOpen("WARNING##SAVEWARNING"))
        ImGui::OpenPopup("WARNING##SAVEWARNING");

    if (ImGui::BeginPopupModal("WARNING##SAVEWARNING", &bOpen))
    {
        ImGui::TextWrapped("Save Level?");
        if (ImGui::Button("Close##ed"))
        {
            bOpen = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Save##ed"))
        {
            UVK::Level::save(UVK::global.levelLocation.c_str());
        }

        ImGui::EndPopup();
    }
}